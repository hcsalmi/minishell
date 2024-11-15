# minishell
A Hive Helsinki school project. Keywords: C, Unix logic<br />
<br />
A project made together with Elina Sirniö (github: Sir-Eli).<br />
<br />
The goal:<br />
The objective of this project was to create a shell, essentially your own bash. The project helps you, among other things, understand processes and file descriptors.<br />
<br />
The specifics:<br />
Your shell should:<br />
• Display a prompt when waiting for a new command.<br />
• Have a working history.<br />
• Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).<br />
• Avoid using more than one global variable to indicate a received signal. Consider the implications: this approach ensures that your signal handler will not access your main data structures. This global variable cannot provide any other  information or data access than the number of a received  signal.  Therefore, using "norm" type structures in the global scope is forbidden.<br />
• Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).<br />
• Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.<br />
• Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).<br />
• Implement redirections:<br />
&emsp;◦ < should redirect input.<br />
&emsp;◦ > should redirect output.<br />
&emsp;◦ << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!<br />
◦ >> should redirect output in append mode.<br /><br />
• Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.<br />
• Handle environment variables ($ followed by a sequence of characters) which should expand to their values.<br />
• Handle $? which should expand to the exit status of the most recently executed foreground pipeline.<br />
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.<br />
• In interactive mode:<br />
&emsp;◦ ctrl-C displays a new prompt on a new line.<br />
&emsp;◦ ctrl-D exits the shell.<br />
&emsp;◦ ctrl-\ does nothing.<br /><br />
• Your shell must implement the following builtins:<br />
&emsp;◦ echo with option -n<br />
&emsp;◦ cd with only a relative or absolute path<br />
&emsp;◦ pwd with no options<br />
&emsp;◦ export with no options<br />
&emsp;◦ unset with no options<br />
&emsp;◦ env with no options or arguments<br />
&emsp;◦ exit with no options<br />
<br />
To run the program, you may need to change the following paths to correspond to your OS. <br />
&emsp;O_FLAGS = -lreadline -L/opt/homebrew/opt/readline/lib<br />
&emsp;C_FLAGS = -I/opt/homebrew/opt/readline/include<br />
(For example, the following command may be useful: brew info readline)<br />

