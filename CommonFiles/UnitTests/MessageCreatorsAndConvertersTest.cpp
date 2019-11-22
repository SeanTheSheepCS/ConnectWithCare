#include "MessageCreatorsAndConvertersTest.h"
#include "../Message.h"
#include "../MessageCodes.h"
#include "../AllMessageTypes.h"
#include "../../ClientFiles/ClientMessageConverter.h"
#include "../../ClientFiles/ClientMessageCreator.h"
#include "../../ServerFiles/ServerMessageConverter.h"
#include "../../ServerFiles/ServerMessageCreator.h"
#include <iostream>

int numberOfTestsPassed = 0; // ONLY CHANGE ME THROUGH TESTS PASSED AND TESTS FAILED!!!!
int numberOfTestsAdministered = 0; // ONLY CHANGE ME THROUGH TESTS PASSED AND TESTS FAILED!!!!

int mainMessageUnitTest()
{
	runUnitTestsForMessages();
	return 0;
}

void runUnitTestsForMessages()
{
	std::cout << "--- MESSAGE UNIT TEST ---" << std::endl;
	runLoginMessageTest();
	runLogoutMessageTest();
	runCreatePostingMessageTest();
	runSendUserMessageMessageTest();
	runBoardHistoryMessageTest();
	runBoardSearchMessageTest();
	runUserMessageHistoryMessageTest();
	runUserMessageHistoryAllMessageTest();
	runLoginAuthMessageTest();
	runLogoutConfirmMessageTest();
	runPostingDataMessageTest();
	runUserMessageDataMessageTest();
	runServerSpecialMessagesTest();
	std::cout << "TESTS PASSED: " << std::dec << numberOfTestsPassed << "/" << std::dec << numberOfTestsAdministered << std::endl;
}

void runLoginMessageTest()
{
	ClientMessageCreator creator = ClientMessageCreator();
	LoginMessage theLoginMessage = creator.createLoginMessage(string("john_doe"), string("passw0rd"));
	//std::cout << "	" << "INPUT" << std::endl;
	//std::cout << "		" << theLoginMessage.getUsername() << std::endl;
	//std::cout << "		" << theLoginMessage.getPassword() << std::endl;
	Message theMessage = theLoginMessage;

	ServerMessageConverter converter;
	if(converter.isLoginMessage(theMessage))
	{
		LoginMessage theLoginMessageConverted = converter.toLoginMessage(theMessage);
		//std::cout << "	" << "OUTPUT" << std::endl;
		//std::cout << "		" << theLoginMessageConverted.getUsername() << std::endl;
		//std::cout << "		" << theLoginMessageConverted.getPassword() << std::endl;
		if(theLoginMessageConverted.getUsername() == "john_doe")
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
		if(theLoginMessageConverted.getPassword() == "passw0rd")
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}

	LoginMessage anotherLoginMessage = creator.createLoginMessage(string("tom"), string("securepassword"));
	//std::cout << "	" << "INPUT" << std::endl;
	//std::cout << "		" << anotherLoginMessage.getUsername() << std::endl;
	//std::cout << "		" << anotherLoginMessage.getPassword() << std::endl;
	Message anotherMessage = anotherLoginMessage;
	if(converter.isLoginMessage(anotherLoginMessage))
	{
		LoginMessage theLoginMessageConverted = converter.toLoginMessage(anotherMessage);
		//std::cout << "	" << "OUTPUT" << std::endl;
		//std::cout << "		" << theLoginMessageConverted.getUsername() << std::endl;
		//std::cout << "		" << theLoginMessageConverted.getPassword() << std::endl;
		if(theLoginMessageConverted.getUsername() == "tom")
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
		if(theLoginMessageConverted.getPassword() == "securepassword")
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
}

void runLogoutMessageTest()
{
	ClientMessageCreator creator = ClientMessageCreator();
	LogoutMessage theLogoutMessage = creator.createLogoutMessage();
	Message theMessage = Message(theLogoutMessage.getLength(), theLogoutMessage.getMessageAsCharArray());

	ServerMessageConverter converter;
	if(converter.isLogoutMessage(theMessage))
	{
		LogoutMessage logoutMessageAgain = converter.toLogoutMessage(theMessage);
		if((logoutMessageAgain.getMessageAsCharArray())[0] == CLIENTMESSAGECODE_LOGOUT)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}

	if(converter.isLoginMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
}

void runCreatePostingMessageTest()
{
	ClientMessageCreator creator = ClientMessageCreator();
	unsigned long int testBoardID = 8000;
	std::string testUsername = string("TESTER");
	Date testDate = Date(2007,10,30,90);
	std::string testPostText = string("I AM A TEST");
	Posting testPosting = Posting(testPostText,testUsername,testDate);
	CreatePostingMessage thecpMessage = creator.createCreatePostingMessage(testBoardID, testPosting);
	Message theMessage = Message(thecpMessage.getLength(), thecpMessage.getMessageAsCharArray());

	ServerMessageConverter converter;
	if(converter.isCreatePostingMessage(theMessage))
	{
		CreatePostingMessage cpMessageAgain = converter.toCreatePostingMessage(theMessage);
		if((cpMessageAgain.getMessageAsCharArray())[0] == CLIENTMESSAGECODE_CREATEPOST)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(cpMessageAgain.getBoardIDThatThePostingBelongsTo() == testBoardID)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(cpMessageAgain.getPosting().getDateTimePosted().equals(testDate))
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(cpMessageAgain.getPosting().getPostText() == testPostText)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(cpMessageAgain.getPosting().getUsernameOfUserWhoCreatedThisPost() == testUsername)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}

	if(converter.isLoginMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
	if(converter.isLogoutMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
}

void runSendUserMessageMessageTest()
{
	ClientMessageCreator creator = ClientMessageCreator();
	ServerMessageConverter converter;

	std::string testSenderUsername = "darth_vader";
	std::string testRecipientUsername = "luke_skywalker";
	Date testDate = Date(1980,5,21,40000);
	std::string testMessageText = "No, I am your father.";
	UserMessage testUserMessage = UserMessage(testSenderUsername, testRecipientUsername, testDate, testMessageText);
	SendUserMessageMessage sumMessage = creator.createSendUserMessageMessage(testUserMessage);
	Message theMessage = Message(sumMessage.getLength(), sumMessage.getMessageAsCharArray());

	if(converter.isSendUserMessageMessage(theMessage))
	{
		SendUserMessageMessage theSendUserMessageMessageAgain = converter.toSendUserMessageMessage(theMessage);
		if((theSendUserMessageMessageAgain.getMessageAsCharArray())[0] == CLIENTMESSAGECODE_SENDMESSAGE)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(theSendUserMessageMessageAgain.getUserMessage().getUsernameOfTheSender() == testSenderUsername)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(theSendUserMessageMessageAgain.getUserMessage().getUsernameOfTheRecipient() == testRecipientUsername)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(theSendUserMessageMessageAgain.getUserMessage().getDateCreated().equals(testDate))
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(theSendUserMessageMessageAgain.getUserMessage().getMessageText() == testMessageText)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}

	if(converter.isLoginMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
	if(converter.isUserMessageHistoryAllMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
	if(converter.isUserMessageHistoryMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
	if(converter.isBoardHistoryMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
	if(converter.isCreatePostingMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
}

void runBoardHistoryMessageTest()
{
	ClientMessageCreator creator = ClientMessageCreator();
	Date testStartDate = Date(1999,8,20,3);
	Date testEndDate = Date(1999,9,18,0);
	unsigned long int testBoardID = 2022;
	BoardHistoryMessage theBHMessage = creator.createBoardHistoryMessage(testStartDate,testEndDate,testBoardID);
	Message theMessage = Message(theBHMessage.getLength(), theBHMessage.getMessageAsCharArray());

	ServerMessageConverter converter;
	if(converter.isBoardHistoryMessage(theMessage))
	{
		BoardHistoryMessage bhMessageAgain = converter.toBoardHistoryMessage(theMessage);

		if((bhMessageAgain.getMessageAsCharArray())[0] == CLIENTMESSAGECODE_BOARDHISTORY)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(bhMessageAgain.getBoardID() == testBoardID)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(testStartDate.equals(bhMessageAgain.getStartDate()))
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(testEndDate.equals(bhMessageAgain.getEndDate()))
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}

	if(converter.isLoginMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	if(converter.isLogoutMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
}

void runBoardSearchMessageTest()
{
	ClientMessageCreator creator = ClientMessageCreator();
	Date testStartDate = Date(2007,4,31,9);
	Date testEndDate = Date(2009,10,1,0);
	unsigned long int testBoardID = 51;
	std::string testSearchTerm = "House";
	BoardSearchMessage theBSMessage = creator.createBoardSearchMessage(testStartDate,testEndDate,testBoardID, testSearchTerm);
	Message theMessage = Message(theBSMessage.getLength(), theBSMessage.getMessageAsCharArray());

	ServerMessageConverter converter;
	if(converter.isBoardSearchMessage(theMessage))
	{
		BoardSearchMessage bsMessageAgain = converter.toBoardSearchMessage(theMessage);

		if((bsMessageAgain.getMessageAsCharArray())[0] == CLIENTMESSAGECODE_BOARDSEARCH)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(bsMessageAgain.getBoardID() == testBoardID)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(testStartDate.equals(bsMessageAgain.getStartDate()))
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(testEndDate.equals(bsMessageAgain.getEndDate()))
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(bsMessageAgain.getSearchKeyword() == testSearchTerm)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}

	if(converter.isLoginMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	if(converter.isLogoutMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
}

void runUserMessageHistoryMessageTest()
{
	ClientMessageCreator creator = ClientMessageCreator();
	Date testStartDate = Date(1999,4,10,23);
	Date testEndDate = Date(2003,5,19,37);
	std::string testUsername = "hugh__JENSEN";
	UserMessageHistoryMessage theUMHMessage = creator.createUserMessageHistoryMessage(testStartDate,testEndDate,testUsername);
	Message theMessage = Message(theUMHMessage.getLength(), theUMHMessage.getMessageAsCharArray());

	ServerMessageConverter converter;
	if(converter.isUserMessageHistoryMessage(theMessage))
	{
		UserMessageHistoryMessage umhMessageAgain = converter.toUserMessageHistoryMessage(theMessage);

		if((umhMessageAgain.getMessageAsCharArray())[0] == CLIENTMESSAGECODE_MESSAGEHISTORY)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(umhMessageAgain.getUsernameToGetHistoryWith() == testUsername)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(testStartDate.equals(umhMessageAgain.getStartDate()))
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(testEndDate.equals(umhMessageAgain.getEndDate()))
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}

	if(converter.isLoginMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	if(converter.isBoardHistoryMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
}

void runUserMessageHistoryAllMessageTest()
{
	ClientMessageCreator creator = ClientMessageCreator();
	Date testStartDate = Date(2007,8,8,100);
	Date testEndDate = Date(2019,11,7,0);
	UserMessageHistoryAllMessage theUMHAMessage = creator.createUserMessageHistoryAllMessage(testStartDate,testEndDate);
	Message theMessage = Message(theUMHAMessage.getLength(), theUMHAMessage.getMessageAsCharArray());
	ServerMessageConverter converter;
	if(converter.isUserMessageHistoryAllMessage(theMessage))
	{
		UserMessageHistoryAllMessage umhaMessageAgain = converter.toUserMessageHistoryAllMessage(theMessage);

		if((umhaMessageAgain.getMessageAsCharArray())[0] == CLIENTMESSAGECODE_MESSAGEHISTALL)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(testStartDate.equals(umhaMessageAgain.getStartDate()))
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(testEndDate.equals(umhaMessageAgain.getEndDate()))
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}

	if(converter.isLoginMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	if(converter.isLogoutMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	if(converter.isUserMessageHistoryMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	if(converter.isBoardHistoryMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
}

void runLoginAuthMessageTest()
{
	ServerMessageCreator creator = ServerMessageCreator();
	LoginAuthMessage theLoginAuthMessage = creator.createLoginAuthMessage(false);
	//std::cout << "	" << "INPUT" << std::endl;
	//std::cout << "		" << "FALSE" << std::endl;
	Message theMessage = Message(theLoginAuthMessage.getLength(), theLoginAuthMessage.getMessageAsCharArray());
	ClientMessageConverter converter;
	if(converter.isLoginAuthMessage(theMessage))
	{
		LoginAuthMessage theLoginAuthMessageConverted = converter.toLoginAuthMessage(theMessage);
		//std::cout << "	" << "OUTPUT" << std::endl;
		if(theLoginAuthMessageConverted.getValidBit() == true)
		{
			//std::cout << "		" << "TRUE" << std::endl;
			testFailed();
		}
		else
		{
			//std::cout << "		" << "FALSE" << std::endl;
			testPassed();
		}
	}

	LoginAuthMessage anotherLoginAuthMessage = creator.createLoginAuthMessage(true);
	//std::cout << "	" << "INPUT" << std::endl;
	//std::cout << "		" << "TRUE" << std::endl;
	Message anotherMessage =Message(anotherLoginAuthMessage.getLength(), anotherLoginAuthMessage.getMessageAsCharArray());
	if(converter.isLoginAuthMessage(anotherMessage))
	{
		LoginAuthMessage theLoginAuthMessageConverted = converter.toLoginAuthMessage(anotherMessage);
		//std::cout << "	" << "OUTPUT" << std::endl;
		if(theLoginAuthMessageConverted.getValidBit() == true)
		{
			//std::cout << "		" << "TRUE" << std::endl;
			testPassed();
		}
		else
		{
			//std::cout << "		" << "FALSE" << std::endl;
			testFailed();
		}
	}
}

void runLogoutConfirmMessageTest()
{
	ServerMessageCreator creator = ServerMessageCreator();
	LogoutConfirmMessage theLogoutConfirmMessage = creator.createLogoutConfirmMessage(false);
	Message theMessage = Message(theLogoutConfirmMessage.getLength(), theLogoutConfirmMessage.getMessageAsCharArray());
	ClientMessageConverter converter;
	if(converter.isLogoutConfirmMessage(theMessage))
	{
		LogoutConfirmMessage theLogoutConfirmMessageConverted = converter.toLogoutConfirmMessage(theMessage);
		if(theLogoutConfirmMessageConverted.getSuccessBit() == true)
		{
			testFailed();
		}
		else
		{
			testPassed();
		}
	}

	LogoutConfirmMessage anotherLogoutConfirmMessage = creator.createLogoutConfirmMessage(true);
	Message anotherMessage = Message(anotherLogoutConfirmMessage.getLength(), anotherLogoutConfirmMessage.getMessageAsCharArray());
	if(converter.isLogoutConfirmMessage(anotherMessage))
	{
		LogoutConfirmMessage theLogoutConfirmMessageConverted = converter.toLogoutConfirmMessage(anotherMessage);
		if(theLogoutConfirmMessageConverted.getSuccessBit() == true)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
}

void runPostingDataMessageTest()
{
	ServerMessageCreator creator = ServerMessageCreator();
	unsigned long int testBoardID = 2048;
	std::string testUsername = string("TESTUSER");
	Date testDate = Date(2080,11,11,0);
	std::string testPostText = string("ANOTHER TEST POSTING");
	Posting testPosting = Posting(testPostText,testUsername,testDate);
	PostingDataMessage thepdMessage = creator.createPostingDataMessage(testPosting, testBoardID);
	Message theMessage = Message(thepdMessage.getLength(), thepdMessage.getMessageAsCharArray());

	ClientMessageConverter converter;
	if(converter.isPostingDataMessage(theMessage))
	{
		PostingDataMessage thepdMessageAgain = converter.toPostingDataMessage(theMessage);
		if((thepdMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_POSTINGDATA)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(thepdMessageAgain.getBoardIDThatThePostingBelongsTo() == testBoardID)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(thepdMessageAgain.getPosting().getDateTimePosted().equals(testDate))
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(thepdMessageAgain.getPosting().getPostText() == testPostText)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(thepdMessageAgain.getPosting().getUsernameOfUserWhoCreatedThisPost() == testUsername)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}

	if(converter.isLoginAuthMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
	if(converter.isEndOfDataMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
}

void runUserMessageDataMessageTest()
{
	ServerMessageCreator creator = ServerMessageCreator();
	ClientMessageConverter converter;

	std::string testSenderUsername = "john_lennon";
	std::string testRecipientUsername = "yoko_ono";
	Date testDate = Date(1987,10,10,26000);
	std::string testMessageText = "Imagine all the people...";
	UserMessage testUserMessage = UserMessage(testSenderUsername, testRecipientUsername, testDate, testMessageText);
	UserMessageDataMessage umdMessage = creator.createUserMessageDataMessage(testUserMessage);
	Message theMessage = Message(umdMessage.getLength(), umdMessage.getMessageAsCharArray());

	if(converter.isUserMessageDataMessage(theMessage))
	{
		UserMessageDataMessage theuserDataMessageAgain = converter.toUserMessageDataMessage(theMessage);
		if((theuserDataMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_MESSAGEDATA)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(theuserDataMessageAgain.getUserMessage().getUsernameOfTheSender() == testSenderUsername)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(theuserDataMessageAgain.getUserMessage().getUsernameOfTheRecipient() == testRecipientUsername)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(theuserDataMessageAgain.getUserMessage().getDateCreated().equals(testDate))
		{
			testPassed();
		}
		else
		{
			testFailed();
		}

		if(theuserDataMessageAgain.getUserMessage().getMessageText() == testMessageText)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}

	if(converter.isLoginAuthMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
	if(converter.isEndOfDataMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
	if(converter.isPostingDataMessage(theMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
}

void runServerSpecialMessagesTest()
{
	ServerMessageCreator creator = ServerMessageCreator();
	ClientMessageConverter converter;

	EndOfDataMessage eodMessage = creator.createEndOfDataMessage();
	Message exampleMessage = Message(eodMessage.getLength(), eodMessage.getMessageAsCharArray());
	if(converter.isEndOfDataMessage(exampleMessage))
	{
		EndOfDataMessage eodMessageAgain = converter.toEndOfDataMessage(exampleMessage);
		if((eodMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_ENDOFDATA)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}
	if(converter.isErrorBoardNotFoundMessage(exampleMessage) || converter.isErrorNoAuthMessage(exampleMessage) || converter.isErrorUserNotFoundMessage(exampleMessage) ||
			converter.isErrorWriteFailedMessage(exampleMessage) || converter.isWriteSuccessfulMessage(exampleMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	ErrorBoardNotFoundMessage ebnfMessage = creator.createErrorBoardNotFoundMessage();
	Message exampleMessageTwo = Message(ebnfMessage.getLength(), ebnfMessage.getMessageAsCharArray());
	if(converter.isErrorBoardNotFoundMessage(exampleMessageTwo))
	{
		ErrorBoardNotFoundMessage ebnfMessageAgain = converter.toErrorBoardNotFoundMessage(exampleMessageTwo);
		if((ebnfMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_ERRORBOARDNOTFOUND)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}
	if(converter.isEndOfDataMessage(exampleMessageTwo) || converter.isErrorNoAuthMessage(exampleMessageTwo) || converter.isErrorUserNotFoundMessage(exampleMessageTwo) ||
			converter.isErrorWriteFailedMessage(exampleMessageTwo) || converter.isWriteSuccessfulMessage(exampleMessageTwo))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	ErrorNoAuthMessage enaMessage = creator.createErrorNoAuthMessage();
	Message exampleMessageThree = Message(enaMessage.getLength(), enaMessage.getMessageAsCharArray());
	if(converter.isErrorNoAuthMessage(exampleMessageThree))
	{
		ErrorNoAuthMessage enaMessageAgain = converter.toErrorNoAuthMessage(exampleMessageThree);
		if((enaMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_ERRORNOAUTH)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}
	if(converter.isEndOfDataMessage(exampleMessageThree) || converter.isErrorBoardNotFoundMessage(exampleMessageThree) || converter.isErrorUserNotFoundMessage(exampleMessageThree) ||
			converter.isErrorWriteFailedMessage(exampleMessageThree) || converter.isWriteSuccessfulMessage(exampleMessageThree))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	ErrorUserNotFoundMessage eunfMessage = creator.createErrorUserNotFoundMessage();
	Message exampleMessageFour = Message(eunfMessage.getLength(), eunfMessage.getMessageAsCharArray());
	if(converter.isErrorUserNotFoundMessage(exampleMessageFour))
	{
		ErrorUserNotFoundMessage enufMessageAgain = converter.toErrorUserNotFoundMessage(exampleMessageFour);
		if((enufMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_ERRORUSERNOTFOUND)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}
	if(converter.isEndOfDataMessage(exampleMessageFour) || converter.isErrorBoardNotFoundMessage(exampleMessageFour) || converter.isErrorNoAuthMessage(exampleMessageFour) ||
			converter.isErrorWriteFailedMessage(exampleMessageFour) || converter.isWriteSuccessfulMessage(exampleMessageFour))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	ErrorWriteFailedMessage ewfMessage = creator.createErrorWriteFailedMessage();
	Message exampleMessageFive = Message(ewfMessage.getLength(), ewfMessage.getMessageAsCharArray());
	if(converter.isErrorWriteFailedMessage(exampleMessageFive))
	{
		ErrorWriteFailedMessage ewfMessageAgain = converter.toErrorWriteFailedMessage(exampleMessageFive);
		if((ewfMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_ERRORWRITEFAILED)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}
	if(converter.isEndOfDataMessage(exampleMessageFive) || converter.isErrorBoardNotFoundMessage(exampleMessageFive) || converter.isErrorNoAuthMessage(exampleMessageFive) ||
			converter.isErrorUserNotFoundMessage(exampleMessageFive) || converter.isWriteSuccessfulMessage(exampleMessageFive))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	WriteSuccessfulMessage wsMessage = creator.createWriteSuccessfulMessage();
	Message exampleMessageSix = Message(wsMessage.getLength(), wsMessage.getMessageAsCharArray());
	if(converter.isWriteSuccessfulMessage(exampleMessageSix))
	{
		WriteSuccessfulMessage wsMessageAgain = converter.toWriteSuccessfulMessage(exampleMessageSix);
		if((wsMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_WRITESUCCESSFUL)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}
	if(converter.isEndOfDataMessage(exampleMessageSix) || converter.isErrorBoardNotFoundMessage(exampleMessageSix) || converter.isErrorNoAuthMessage(exampleMessageSix) ||
			converter.isErrorUserNotFoundMessage(exampleMessageSix) || converter.isErrorWriteFailedMessage(exampleMessageSix))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
}

void testPassed()
{
	numberOfTestsPassed++;
	numberOfTestsAdministered++;
}

void testFailed()
{
	numberOfTestsAdministered++;
}

