#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefds[2];
    if (pipe(pipefds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // 子プロセス：lsを実行
        close(pipefds[0]);  // 子プロセスではパイプの読み取り側を閉じる
        if (dup2(pipefds[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipefds[1]);  // 使用済みのファイルディスクリプタを閉じる

        execlp("ls", "ls", NULL);
        perror("execlp ls");  // execが失敗した場合のエラーメッセージ
        exit(EXIT_FAILURE);
    } else {
        // 親プロセス：grepを実行
		wait(NULL);
        close(pipefds[1]);  // 親プロセスではパイプの書き込み側を閉じる
        if (dup2(pipefds[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipefds[0]);  // 使用済みのファイルディスクリプタを閉じる

        execlp("grep", "grep", ".txt", NULL);
        perror("execlp grep");  // execが失敗した場合のエラーメッセージ
        exit(EXIT_FAILURE);
    }

    return 0;
}

