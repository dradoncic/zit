#include "../include/utils.h"
#include "../include/commands.h"
#include <stdio.h>
#include <stdlib.h>

command commands[] = {
    {"add", cmd_add, "Add file contents to the index"},
    {"cat-file", cmd_cat_file, "Provide content or type and size information for repository objects"},
    {"check-ignore", cmd_check_ignore, "Debug gitignore / exclude files"},
    {"checkout", cmd_checkout, "Checkout a branch or paths to the working tree"},
    {"commit", cmd_commit, "Record changes to the repository"},
    {"hash-object", cmd_hash_object, "Compute object ID and optionally creates a blob from a file"},
    {"init", cmd_init, "Create an empty Git repository or reinitialize an existing one"},
    {"log", cmd_log, "Show commit logs"},
    {"ls-files", cmd_ls_files, "Show information about files in the index and the working tree"},
    {"ls-tree", cmd_ls_tree, "List the contents of a tree object"},
    {"rev-parse", cmd_rev_parse, "Parse revision (or other objects) identifiers"},
    {"rm", cmd_rm, "Remove files from the working tree and from the index"},
    {"show-ref", cmd_show_ref, "List references in a local repository"},
    {"status", cmd_status, "Show the working tree status"},
    {"tag", cmd_tag, "Create, list, delete or verify a tag object signed with GPG"},
    {NULL, NULL, NULL}
};

void usage(const char *progname) {
    fprintf(stderr, "Usage: %s <command> [<args>]\n\n", progname);
    fprintf(stderr, "Available commands:\n");
    
    for (command *cmd = commands; cmd->name; cmd++) {
        fprintf(stderr, "  %-12s %s\n", cmd->name, cmd->help);
    }
    
    exit(1);
}
