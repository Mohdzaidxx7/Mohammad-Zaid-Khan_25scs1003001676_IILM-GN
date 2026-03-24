# app.py
import os
import io
import math
import pandas as pd
import numpy as np
import streamlit as st
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

st.set_page_config(page_title="Plagiarism Checker", layout="wide")

# --- Helper functions ------------------------------------------------------
def read_uploaded_file(uploaded_file):
    """Return text contents of a streamlit uploaded file (bytes -> str)."""
    try:
        raw = uploaded_file.read()
        # try utf-8, fallback to latin-1 to avoid decode errors
        return raw.decode("utf-8")
    except Exception:
        try:
            return raw.decode("latin-1")
        except Exception:
            return ""

def read_files_from_folder(folder_path):
    """Read .txt files from a local folder path (for testing)."""
    files = []
    for fname in sorted(os.listdir(folder_path)):
        if fname.lower().endswith(".txt"):
            try:
                with open(os.path.join(folder_path, fname), encoding="utf-8") as f:
                    files.append((fname, f.read()))
            except Exception:
                with open(os.path.join(folder_path, fname), encoding="latin-1") as f:
                    files.append((fname, f.read()))
    return files

def build_tfidf_matrix(texts):
    """Return TF-IDF matrix for a list of texts."""
    vect = TfidfVectorizer().fit_transform(texts)
    return vect

def compute_similarity_matrix(tfidf_matrix):
    """Compute cosine similarity matrix (square NxN)."""
    sim = cosine_similarity(tfidf_matrix)
    # numerical safety: clip to [0,1]
    sim = np.clip(sim, 0.0, 1.0)
    return sim

def pairwise_results(file_names, sim_matrix, threshold=0.0, top_n=None):
    """Return a DataFrame with pairwise similarity results above threshold.
       top_n: if provided, return only the top N pairs by score.
    """
    n = len(file_names)
    rows = []
    for i in range(n):
        for j in range(i + 1, n):
            score = float(sim_matrix[i, j])
            if score >= threshold:
                rows.append((file_names[i], file_names[j], score))
    df = pd.DataFrame(rows, columns=["File A", "File B", "Similarity"])
    if df.empty:
        return df
    df["Percent"] = (df["Similarity"] * 100).round(2)
    df = df.sort_values("Similarity", ascending=False).reset_index(drop=True)
    if top_n:
        df = df.head(top_n)
    return df

def highlight_high_similarity(val, cutoff):
    """Return CSS for table highlighting."""
    if val >= cutoff:
        return "background-color: #ffcccc"  # light red
    return ""

# --- Streamlit UI ----------------------------------------------------------
st.title("📄 Plagiarism Checker — TF-IDF + Cosine Similarity")
st.markdown(
    """
Upload multiple `.txt` files (student submissions). The app calculates
pairwise similarity and shows suspicious pairs.  
*Notes:* TF-IDF + cosine is a good baseline for surface/textual similarity.
"""
)

# Sidebar controls
st.sidebar.header("Options")
mode = st.sidebar.radio("Input source", ["Upload files (multiple)", "Read local folder"])
threshold_percent = st.sidebar.slider("Minimum similarity (%) to report", 0, 100, 30)
top_n = st.sidebar.number_input("Show top N pairs (0 = all)", min_value=0, value=0, step=1)
use_percent_display = st.sidebar.checkbox("Show percent (%) column", value=True)
show_matrix = st.sidebar.checkbox("Show full similarity matrix", value=False)

uploaded_files = []
file_data = []

if mode == "Upload files (multiple)":
    uploaded_files = st.file_uploader("Upload .txt files", type=["txt"], accept_multiple_files=True)
    if uploaded_files:
        st.success(f"{len(uploaded_files)} file(s) uploaded.")
        for f in uploaded_files:
            text = read_uploaded_file(f)
            filename = getattr(f, "name", "unknown.txt")
            file_data.append((filename, text))

else:
    st.info("Enter a local folder path (useful for testing on your machine).")
    folder = st.text_input("Local folder path (e.g. ./samples)", value="")
    if folder:
        if os.path.isdir(folder):
            file_data = read_files_from_folder(folder)
            st.success(f"Found {len(file_data)} .txt file(s) in folder.")
        else:
            st.error("Folder not found. Please type a correct folder path.")

if not file_data:
    st.warning("No files loaded yet — upload files or enter a folder path.")
    st.stop()

# Show loaded filenames
file_names = [t[0] for t in file_data]
st.subheader("Loaded files")
cols = st.columns([3, 7])
with cols[0]:
    st.info("Files")
    for fn in file_names:
        st.write(f"- {fn}")
with cols[1]:
    st.info("First 400 characters preview (first file)")
    st.write(file_data[0][1][:400].replace("\n", " "))

# Prepare texts and compute TF-IDF
texts = [t[1] for t in file_data]
try:
    with st.spinner("Vectorizing texts (TF-IDF) and computing similarities..."):
        tfidf = build_tfidf_matrix(texts)
        sim_matrix = compute_similarity_matrix(tfidf)
except Exception as e:
    st.error(f"Error computing TF-IDF/similarity: {e}")
    st.stop()

# Show matrix if requested
if show_matrix:
    st.subheader("Similarity matrix (values 0-1)")
    mat_df = pd.DataFrame(sim_matrix, index=file_names, columns=file_names)
    st.dataframe(mat_df.style.format("{:.4f}"))

# Build pairwise results
threshold = threshold_percent / 100.0
display_top_n = None if top_n == 0 else int(top_n)
results_df = pairwise_results(file_names, sim_matrix, threshold=threshold, top_n=display_top_n)

st.subheader("Suspicious pairs")
if results_df.empty:
    st.success("No pairs exceed the chosen threshold.")
else:
    # display with conditional formatting on Percent/Similarity
    display_df = results_df.copy()
    if use_percent_display:
        display_df = display_df[["File A", "File B", "Percent"]]
        st.dataframe(display_df.style.applymap(
            lambda v: "background-color: #ffcccc" if (isinstance(v, (int, float)) and v >= (threshold_percent)) else "",
            subset=["Percent"]
        ))
    else:
        st.dataframe(display_df[["File A", "File B", "Similarity"]].style.format({"Similarity": "{:.4f}"}))

    # Provide CSV download
    csv_bytes = results_df.to_csv(index=False).encode("utf-8")
    st.download_button("Download CSV of pairs", data=csv_bytes, file_name="plagiarism_pairs.csv", mime="text/csv")

# Extra: show top matching snippets for the top pair (simple)
if not results_df.empty:
    st.subheader("Top match preview")
    top = results_df.iloc[0]
    a_idx = file_names.index(top["File A"])
    b_idx = file_names.index(top["File B"])
    ta = texts[a_idx]
    tb = texts[b_idx]
    cols = st.columns(2)
    with cols[0]:
        st.markdown(f"**{top['File A']}** (first 1000 chars)")
        st.write(ta[:1000])
    with cols[1]:
        st.markdown(f"**{top['File B']}** (first 1000 chars)")
        st.write(tb[:1000])

st.markdown("---")
st.markdown("Made with ❤️ — TF-IDF + cosine similarity baseline. For robust detection add n-gram checks, fuzzy matching, or copy-paste fingerprinting.")
