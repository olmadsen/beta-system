#include <windows.h>

extern int beta_instance;
extern int beta_previnstance;
extern LPSTR beta_cmdline;
extern int beta_show;

int get_beta_instance () { return beta_instance; }

int get_beta_previnstance () { return beta_previnstance; }

LPSTR get_beta_cmdline () { return beta_cmdline; }

int get_beta_show () { return beta_show; }

long copyinput(long input)
{
	return input;
}
