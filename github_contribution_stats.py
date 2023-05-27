#!/usr/bin/env python3

from git import Repo
import os
from collections import defaultdict
import sys

# Check if git python library is installed
try:
    import git
except ImportError as e:
    sys.exit("Error: GitPython library not found. Install it by running 'pip install GitPython'")

# Function to get total lines and commits
def get_total_lines_commits(repo):
    total_lines = sum(1 for _ in repo.git.ls_files().split('\n'))
    total_commits = sum(1 for _ in repo.iter_commits())
    return total_lines, total_commits

# Get user input
repo_path = input("Enter the absolute path of the git repo:\n")

# Check if the repo path exists
if not os.path.exists(repo_path):
    sys.exit("Error: The provided path does not exist.")

# Check if the path is a git repository
try:
    repo = git.Repo(repo_path)
except git.InvalidGitRepositoryError:
    sys.exit("Error: The provided path is not a valid git repository.")

total_lines, total_commits = get_total_lines_commits(repo)

# Initialize defaultdicts
lines_by_author = defaultdict(int)
commits_by_author = defaultdict(int)

# Iterate over all commits for the repo
for commit in repo.iter_commits():
    commits_by_author[commit.author.name] += 1

    try:
        for stats in commit.stats.files.values():
            lines_by_author[commit.author.name] += stats['lines']
    except ValueError:
        pass

# Print the header
print(f"{'Contributor':<20}{'Lines':<10}{'Commits':<10}{'Lines%':<10}{'Commits%':<10}")

# Print the data
for author, lines in sorted(lines_by_author.items(), key=lambda x: x[1], reverse=True):
    commits = commits_by_author[author]
    line_percent = (lines / total_lines) * 100
    commit_percent = (commits / total_commits) * 100

    print(f"{author:<20}{lines:<10}{commits:<10}{line_percent:<10.2f}{commit_percent:<10.2f}")
