#!/bin/bash

# Function to load all commits
function load_commits() {
    local commit_list=()
    local counter=0

    # Get the commit list
    while IFS= read -r line; do
        commit_hash=$(echo "$line" | cut -d' ' -f1)
        commit_timestamp=$(echo "$line" | cut -d' ' -f3)
        commit_message=$(echo "$line" | cut -d' ' -f4-)
        counter=$((counter + 1))
        commit_list[$counter]="$commit_hash $commit_timestamp $commit_message"
    done < <(git log --pretty=format:"%h %cd %s" --date=iso)

    # Display the commit list
    for ((i = counter; i >= 1; i--)); do
        echo "[$i] ${commit_list[$i]}"
    done

    return $counter
}

# Prompt the user to select the commit to revert
echo "Select the commit to revert:"
commit_counter=$(load_commits)

read -p "Enter the number of the commit to revert (or 'q' to quit): " commit_number

# Check if the user wants to quit
if [ "$commit_number" == "q" ]; then
    exit 0
fi

# Validate the commit number
if ! [[ "$commit_number" =~ ^[0-9]+$ ]] || [ "$commit_number" -lt 1 ] || [ "$commit_number" -gt "$commit_counter" ]; then
    echo "Invalid commit number. Please enter a valid commit number."
    exit 1
fi

# Extract the commit hash from the selected commit
commit_hash=$(echo "${commit_list[$commit_number]}" | cut -d' ' -f1)

# Create a new branch name based on the commit hash
branch_name="revert-commit-$(echo $commit_hash | cut -c1-7)"

# Check if the branch already exists
if git show-ref --quiet --verify "refs/heads/$branch_name"; then
    echo "Branch '$branch_name' already exists. Please delete or rename it and try again."
    exit 1
fi

# Revert the commit
if ! git revert --no-commit $commit_hash; then
    echo "Failed to revert the commit '$commit_hash'. Please check the commit hash and try again."
    exit 1
fi

# Create a new branch with the reverted changes
git checkout -b $branch_name

# Display success message
echo "Successfully reverted commit '$commit_hash' and created branch '$branch_name'."

# Print the full commit
git show $commit_hash

exit 0
