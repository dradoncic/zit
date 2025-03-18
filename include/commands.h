#ifndef COMMANDS_H
#define COMMANDS_H

int cmd_add(int argc, char *argv[]);
int cmd_cat_file(int argc, char *argv[]);
int cmd_check_ignore(int argc, char *argv[]);
int cmd_checkout(int argc, char *argv[]);
int cmd_commit(int argc, char *argv[]);
int cmd_hash_object(int argc, char *argv[]);
int cmd_init(int argc, char *argv[]);
int cmd_log(int argc, char *argv[]);
int cmd_ls_files(int argc, char *argv[]);
int cmd_ls_tree(int argc, char *argv[]);
int cmd_rev_parse(int argc, char *argv[]);
int cmd_rm(int argc, char *argv[]);
int cmd_show_ref(int argc, char *argv[]);
int cmd_status(int argc, char *argv[]);
int cmd_tag(int argc, char *argv[]);


#endif 
