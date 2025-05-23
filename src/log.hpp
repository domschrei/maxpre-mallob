#ifndef MAXPP_LOG_HPP
#define MAXPP_LOG_HPP

#include <iostream>
#include <cstdint>
#include <vector>

#include "timer.hpp"

namespace maxPreprocessor {
class LogT {
public:
	int rClauses, rVariables, rLiterals, rLabels;
	LogT();
	void print(std::ostream& out);
};

class Log {
public:
	enum Technique {none, BCE, UP, BVE, SE, SSR, SLE, BCR, SIE, EE, BVA, GSLE, FLP, UH, LS, AM1, TMS, BBTMS, LRED, CRED, MRED, URED, HARD, FLE};
	std::vector<double> eTime;
	std::vector<double> tTimeLimit;
	std::vector<Technique> askHistory;
	const double infTime = 1e9;
	double toReallocate;
	double timeLimit;
	Technique activeTechnique;
	Timer totalTimer;
	std::vector<LogT> tLog;
	std::vector<Timer> tTimer;
	int gatesExtracted;
	int labelsMatched;
	int binaryCoresFound;
	bool interrupted;
	volatile bool asyncInterruptSet {false};
	Log();
	Technique charToTechnique(char t);
	void startTechnique(Technique t);
	void stopTechnique(Technique t);
	void removeClause(int c);
	void removeVariable(int c);
	void removeLiteral(int c);
	void removeLabel(int c);
	void print(std::ostream& out);
	double getTime(Technique t);
	void startTimer();
	void stopTimer();
	void timePlan(double timeLimit_, std::string useTechniques);
	bool requestTime(Technique t);
	double allocatedTimeLeft(Technique t);
	void newRequest(Technique t);
	void neverAgain(char t);
	bool isTimeLimit();
	void printTime(std::ostream& out);
	void printInfo(std::ostream& out);
	void interruptAsynchronously() {asyncInterruptSet = true;}
	bool isInterruptedAsynchronously() {interrupted |= asyncInterruptSet; return asyncInterruptSet;}
	std::vector<uint64_t> initialWeightRange;
	std::vector<uint64_t> weightRange;
};
}
#endif
