# 🐚 Minishell: Your Tiny but Mighty Shell

This project was an awesome deep dive into the heart of how Unix shells work! I built a fully functional miniature shell in C, mimicking the core features you see in Bash. The challenge? Doing it all from scratch, without relying on high-level libraries. It was all about understanding the raw power of system calls and low-level programming.

## ✨ What I Learned & Implemented:

* **Command Parsing & Execution:** Taking your typed commands and figuring out what to do with them. Think of it as the shell's brain deciphering your instructions.
* **Pipes (|) and Redirection (>, <, >>):** Making data flow! Connecting the output of one command to the input of another, and shuffling data to and from files.
* **Signal Handling (Ctrl+C, Ctrl+\\):** Learning how to gracefully respond to interruptions like `SIGINT` and `SIGQUIT`. No crashing allowed!
* **Environment Variable Management:** Handling those `$PATH` and `$HOME` variables that make your system work.
* **Process Management (fork(), execve()):** The magic of creating new processes to run your commands and then executing them.
* **No High-Level Libraries:** This was the real challenge! Everything was built using fundamental C functions and system calls.

## 🛠️ Getting Started:

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/AKL001/MiniShell.git
    cd minishell
    ```

2.  **Compile the project:**
    Just run `make` in the project directory:
    ```bash
    make
    ```

3.  **Run the shell:**
    Once compiled, execute the `minishell` binary:
    ```bash
    ./minishell
    ```

4.  **Exit the shell:**
    Simply type `exit` and press Enter.

## ⚙️ Prerequisites:

* **C Compiler (gcc):** You'll need a C compiler to build the project.
* **Linux or macOS Environment:** This project relies on specific system calls and signal handling mechanisms common in these environments.

This project was a fantastic journey into systems programming, and I'm excited to build upon this foundation! 🚀
