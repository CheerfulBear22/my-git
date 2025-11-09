/*
git full-update

A command to combine git add, git commit, and git push
*/

#include "builtin.h"
#include "cache.h"
#include "run-command.h"

static const char * const full_update_usage[] = {
	"git full-update [-m <message>]",
	NULL
};

int cmd_full_update(int argc, const char **argv, const char *prefix) {
	const char *msg = "full update";
	struct child_process cp = CHILD_PROCESS_INIT;

	if (argc > 2 && !strcmp(argv[1], "-m")) {
		msg = argv[2];
	}

	cp.git_cmd = 1;
	argv_array_push(&cp.args, "add");
	argv_array_push(&cp.args, "--all");
	argv_array_push(&cp.args, ".");

	if (run_command(&cp)){
		return 1;
	}
	argv_array_clear(&cp.args);

	cp.git_cmd = 1;
	argv_array_push(&cp.args, "push");
	if (run_command(&cp))
		return 1;

	return 0;
}

