#ifndef MY_READLINE_H
# define MY_READLINE_H

	char	*readline (const char *prompt);
	int		add_history(const char *string_for_history);
	int		rl_on_new_line(void);
	void	rl_redisplay(void);
	void	rl_replace_line (const char *text, int clear_undo);

#endif