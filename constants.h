#pragma once

namespace Commands {
	const char SIGNUP[] = "signup";
	const char LOGIN[] = "login";
	const char LOGOUT[] = "logout";
	const char SEARCH[] = "search";
	const char CREATE[] = "create";
	const char OPEN[] = "open";
	const char POST[] = "post";
	const char P_OPEN[] = "p_open";
	const char COMMENT[] = "comment";
	const  char COMMENTS[] = "comments";
	const char REPLY[] = "reply";
	const char UPVOTE[] = "upvote";
	const char DOWNVOTE[] = "downvote";
	const char P_CLOSE[] = "p_close";
	const char QUIT[] = "quit";
	const char EXIT[] = "exit";
	const char WHOAMI[] = "whoami";
	const char ABOUT[] = "about";
	const char LIST[] = "list";
	const char ONE[] = "1";
}
namespace Constants {
	const size_t MAX_ID_SIZE = 20;
	const size_t MAX_COMMAND_SIZE = 100;
}
namespace FileNames {
	const char topicsBinaryFile[] = "topics.dat";
	const char usersBinaryFile[] = "users.dat";
	const char postIdentificatorFileName[] = "postIdentificator.txt";
	const char topicsIdetificatorFileName[] = "topicIdentificator.txt";
	const char commentIdentificatorFileName[] = "commentIdentifcator.txt";
	const char usersIdentificatorFileName[] = "userIdentificator.txt";
}