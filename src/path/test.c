#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"


// Função para contar o número de comandos na lista encadeada
int count_commands(t_token *cmd) {
  t_token *tmp;
  int count = 0;
  
  tmp = cmd;
  while (tmp->next) {
    count++;
    tmp = tmp->next;
  }
  return count;
}

// Função para executar a pipeline com base na lista encadeada de comandos
void pipeline(t_token *cmd, char **args, char **envp) {
  int i, j = 0;
  pid_t pid;
  int cmd_len = count_commands(cmd);
  int fd[2 * cmd_len];

  // pipe(2) for cmd_len times
  for (i = 0; i < cmd_len; i++) {
    if (pipe(fd + i * 2) < 0) {
      perror("couldn't pipe");
      exit(EXIT_FAILURE);
    }
  }

  while (cmd != NULL) {
    fprintf(stderr, "cmd: %s\n", cmd->id.built);
    if ((pid = fork()) == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      // if there is next
      if (cmd->next != NULL) {
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

      if (execve(cmd->id.built, args, envp) < 0) {
        perror(cmd->id.built);
        exit(EXIT_FAILURE);
      }
    } else if (pid < 0) {
      perror("error");
      exit(EXIT_FAILURE);
    }

    // no wait in each process,
    // because I want children to exec without waiting for each other
    // as bash does.
    cmd = cmd->next;
    //fprintf(stderr, "new cmd: %s %s\n", built, cmd->id.built);
    j += 2;
  }

  // close fds in parent process
  for (i = 0; i < 2 * cmd_len; i++) {
    close(fd[i]);
  }

  // wait for children
  for (i = 0; i < cmd_len; i++) wait(NULL);
}