/*
git full-update

A command to combine git add, git commit, and git push
*/

#include "builtin.h"
#include "git-compat-util.h"
#include "repository.h"
#include "run-command.h"

static const char * const full_update_usage[] = {
	"git full-update [-m <message>]",
	NULL
};

int cmd_full_update(int argc, const char **argv, const char *prefix, struct repository *repo) {
	const char *msg = "full update";

	struct child_process cp = CHILD_PROCESS_INIT;

	cp.git_cmd = 1;

	strvec_push(&cp.args, "add");
	strvec_push(&cp.args, "--all");
	strvec_push(&cp.args, ".");
	if (run_command(&cp))
		return 1;
	strvec_clear(&cp.args);

	strvec_push(&cp.args, "commit");
	strvec_push(&cp.args, "-m");
	strvec_push(&cp.args, msg);
	if (run_command(&cp))
		return 1;
	strvec_clear(&cp.args);

	strvec_push(&cp.args, "push");
	if (run_command(&cp))
		return 1;

	return 0;
}
