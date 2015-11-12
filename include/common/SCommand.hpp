#ifndef SCOMMAND_HPP_INCLUDED
#define SCOMMAND_HPP_INCLUDED

enum SCommand : signed char {
	NotAuthorized = -127,
	TooBig,
	AlreadyExist,
	Created,
	VoidFileName,
	VoidDirectory,
	FileDoesNotExist,
	ServerFailure,
	UnknownIssue,
	BadID,
	InvalidPath,
	BadChar,

	ClientFailure,

	ServerReady = 0,
	ClientReady = 0,
	EndOfStream = 0,
	GoodID = 0,
	Succes = 0,

	Upload = 1,
	Download,
	Ls,
	Disconnect,
	Cd,
	Exist,
	Mkdir,
	Passwd,
	Msg,
	Invite
};

#endif
