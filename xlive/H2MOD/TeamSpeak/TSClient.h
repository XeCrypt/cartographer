#ifndef TSCLIENT_H
#define TSCLIENT_H

#include <thread>
#include <unordered_map>
#include "teamspeak\public_definitions.h"

class TSClient {

friend class TSServer;

public:
	TSClient(bool log);
	virtual ~TSClient();

	IN_ADDR getServerAddress();
	BOOL isConnected();
	void startChatting();
	void setServerAddress(IN_ADDR address);
	void setServerPort(unsigned int port);
	void setNickname(char* nickname);
	void setVoiceActivationLevel(float level);
	void mute(anyID clientToMute);
	void unmute(anyID clientToMute);
	bool isMuted(anyID clientId);
	void disconnect();

private:
	BOOL connected = false;
	char* identity;
	uint64 scHandlerID;
	unsigned int error;
	char* nickname;
	unsigned int port;
	IN_ADDR serverAddress;

	static const float MAX_CLIENT_VOLUME_MODIFIER;
	static const float MIN_CLIENT_VOLUME_MODIFIER;

	anyID getClientId(char* name);
	static void handleLobbyTalk(anyID teamspeakClientID, XUID remoteId);
	static void handleStopTalking(anyID teamspeakClientID, XUID remoteId, XUID clientId, char* remoteXuidStr);
	void connect();
	void openPlayback();
	void openMicrophone();
	void initializeCallbacks(bool log);
	void setClientVolume(anyID teamspeakClientID, float volume);
	void printCurrentClientVolume(anyID teamspeakClientID);
	int TSClient::getClientVolume(anyID teamspeakClientID);
	char* programPath(char* programInvocation);
	static void onUserLoggingMessageEvent(const char* logMessage, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* completeLogString);
	static void onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber);
	static void onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage);
	static void onClientMoveTimeoutEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage);
	static void onTalkStatusChangeEvent(uint64 serverConnectionHandlerID, int status, int isReceivedWhisper, anyID clientID);
	static void onServerErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage);
};

#endif