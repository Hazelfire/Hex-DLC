#include "HexDLC.h"

#include <math.h>
#include "MyRandom.h"
#include "Network.h"
#include "Game.h"
#include "FileIO.h"
#include <iostream>

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

HexDLC::HexDLC() :mPopulation(true)
{
}

void HexDLC::run() {

	while (mDLCRunning) {
		std::cout << "Generation evolved" << std::endl;
		mPopulation = Population::evolve(mPopulation);
		mPopulation.sortMembers();

		if (mChampionRequested) {
			mChampion = new Member(mPopulation.getMember(POP_SIZE - 1));
			mChampionRequested = false;
		}
	}
}

void HexDLC::stop()
{
	mDLCRunning = false;
}

Member HexDLC::getChampion()
{
	mChampionRequested = true;
	while (mChampion == nullptr) {
		boost::this_thread::sleep(boost::posix_time::milliseconds(10));
	}
	Member champion = *mChampion;
	delete mChampion;
	mChampion = nullptr;
	return champion;
}
