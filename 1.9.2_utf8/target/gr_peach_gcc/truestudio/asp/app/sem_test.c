#include <kernel.h>
#include <t_syslog.h>
#include "target_syssvc.h"
#include "kernel_cfg.h"
#include "syssvc/syslog.h"

#include "sem_test.h"
#include "sample1.h"

/*
 *  並行実行されるタスク
 */


void taskSend(intptr_t exinf){

	volatile ulong_t	i;
	int_t		tskno = (int_t) exinf;
	char		c;
	ER		ercd;

	while(true){
		syslog(LOG_NOTICE, "taskSend is running");
		for (i = 0; i < task_loop; i++);

		c = message[tskno-1];
		message[tskno-1] = 0;
		switch (c) {
			case 'e':
				syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
				SVC_PERROR(ext_tsk());
				assert(0);
			case 's':
				syslog(LOG_INFO, "#%d#slp_tsk_chung()", tskno);
				SVC_PERROR(slp_tsk());
				break;
			default:
				break;
		}

		ercd = wai_sem(SEM1);---------------

		counter ++;
		syslog(LOG_INFO, "counter = %d", counter);
		syslog(LOG_INFO, "Sem in Sender are running");
		SVC_PERROR(dly_tsk(10000));

		ercd = sig_sem(SEM1);----------------

	}
	syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
	SVC_PERROR(ext_tsk());
}

void taskReceive(intptr_t exinf){

	volatile ulong_t	i;
	int_t		tskno = (int_t) exinf;
	char		c;
	ER		ercd;

	while(true){
		syslog(LOG_NOTICE, "taskReceive is running");
		for (i = 0; i < task_loop; i++);

		c = message[tskno-1];
		message[tskno-1] = 0;

		switch (c) {
			case 'e':
				syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
				SVC_PERROR(ext_tsk());
				assert(0);

			case 's':
				syslog(LOG_INFO, "#%d#slp_tsk_chung()", tskno);
				SVC_PERROR(slp_tsk());
				break;
			default:
				break;
		}

		ercd = wai_sem(SEM1);-----------

		counter ++;
		syslog(LOG_INFO, "counter = %d", counter);
		syslog(LOG_INFO, "Sem in Receive are running");

		ercd = sig_sem(SEM1);-------------


	}
	syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
	SVC_PERROR(ext_tsk());
}
