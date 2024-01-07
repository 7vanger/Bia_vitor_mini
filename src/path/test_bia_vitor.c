#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include  <sys/wait.h>
#include "minishell.h"
// just count number of commands
int count(t_token *token) {
    t_token *tmp;
    int i;
    i = 0;
    tmp = token;
    while (tmp->next)
    {
        tmp = tmp->next;
        i++;
    } 
    return i;
}

void pipeline(t_token *token, char **envp) {
  int i, j = 0;
  pid_t pid;
  int cmd_len = count(token);
  int fd[2 * cmd_len];

  // pipe(2) for cmd_len times
  for (i = 0; i < cmd_len; i++) {
    if (pipe(fd + i * 2) < 0) {
      perror("couldn't pipe");
      exit(EXIT_FAILURE);
    }
  }
  while (token != NULL) {
    if ((pid = fork()) == -1) {
      perror("fork");
      exit(1);
    } else if (pid == 0) {
      // if there is next
      if (token->next != NULL) {
        if (dup2(fd[j + 1], 1) < 0) {
          perror("dup2");
          exit(EXIT_FAILURE);
        }
      }
      // if there is previous
      if (j != 0) {
        if (dup2(fd[j - 2], 0) < 0) {
          perror("dup2");
          exit(EXIT_FAILURE);
        }
      }

      for (i = 0; i < 2 * cmd_len; i++) {
        close(fd[i]);
      }

      if (execve(token->id.built, separate_token(&token->id), envp) < 0) {
        perror(token->id.built);
        exit(EXIT_FAILURE);
      }
    } else if (pid < 0) {
      perror("error");
      exit(EXIT_FAILURE);
    }

    // no wait in each process,
    // because I want children to exec without waiting for each other
    // as bash does.
    token = token->next;
    j += 2;
  }
  // close fds in parent process
  for (i = 0; i < 2 * cmd_len; i++) {
    close(fd[i]);
  }
  // wait for children
  for (i = 0; i < cmd_len; i++) wait(NULL);
}

/* int main(int argc, char *argv[]) {
  char *ls[] = {"ls","-l", NULL};
  char *rev[] = {"rev", NULL};
  char *nl[] = {"nl", NULL};
  char *cat[] = {"cat", NULL};
  char *wc[] = {"wc", "-c", NULL};
  char *head[] = {"head", "-c", "1000", NULL};
  char *time[] = {"time", "-p", "sleep", "3", NULL};
  char *echo[] = {"echo", "toto", NULL};
  char *grep[] = {"grep", "22", NULL};

  char **cmd[] = {ls, grep, NULL, NULL};

  pipeline(cmd);
  return (0);
} */

