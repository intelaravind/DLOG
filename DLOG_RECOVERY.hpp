/*
 * DLOG_RECOVERY.hpp
 *
 *  Created on: Dec 15, 2013
 *      Author: aravind
 */

#ifndef DLOG_RECOVERY_HPP_
#define DLOG_RECOVERY_HPP_

 #include <unistd.h>

void DLOG_create_recovery(std::string dlogpath, std::string userpath)
{

	std::fstream frecovery ;

	std::string fullpath = userpath + "/recovery.sh";

	frecovery.open(fullpath.c_str(), std::fstream::out);



	frecovery << "#!/bin/bash"<<"\n";
	frecovery << "#Author Aravind"<<"\n\n";
	frecovery << "DLOG_PATH="<<dlogpath<<"\n";
	frecovery << "echo $search_dir"<<"\n";
	frecovery << "for entry in \"$search_dir\"/*.tag"<<"\n";
	frecovery << "do"<<"\n";
	frecovery << "$DLOG_PATH/DLOG_FINALIZER.out ${entry%.*}"<<"\n";
	frecovery << "done"<<"\n";

	frecovery.close();

}

#endif /* DLOG_RECOVERY_HPP_ */
