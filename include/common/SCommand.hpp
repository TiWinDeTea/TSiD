#ifndef SCOMMAND_HPP_INCLUDED
#define SCOMMAND_HPP_INCLUDED

enum SCommand : signed char {
	NotAuthorized = -127,
	TooBig,
	AlreadyExist,
	VoidFileName,
	FileDoesNotExist,
	ServerFailure,
	UnknownIssue,

	ClientFailure,

	ServerReady = 0,
	ClientReady = 0,
	EndOfStream = 0,

	Upload = 1,
	Download,
	Ls,
	Disconnect,
	Pwd,
	Cd
};

#endif
