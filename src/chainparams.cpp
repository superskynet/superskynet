// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x75;
        pchMessageStart[1] = 0x31;
        pchMessageStart[2] = 0x22;
        pchMessageStart[3] = 0x06;
        vAlertPubKey = ParseHex("048146f47ad5dc7c1d0e7e17cab37b210ca835a79f5de115bf4060786a65cc3e4986b100e19ae4adb61350a5ed884d4b8b8169442b84903ceff968a6620e56720c");
        nDefaultPort = 11201;
        nRPCPort = 11202;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "Super Skynet is Coming. New pecfect world! New life!";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1504081800, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1504081800;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1315189;

        hashGenesisBlock = genesis.GetHash();
        if (genesis.GetHash() != uint256("0x00000bb4674a7aea871240253ddeaf3efe72668d252c4d8b4583bb150f8e39b4"))
		{
			printf("Searching for genesis block...\n");
			uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
			uint256 thash;
			while (true)
			{
				thash = genesis.GetHash();
				if (thash <= hashTarget)
					break;
				if ((genesis.nNonce & 0xFFFF) == 0)
				{
					printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
				}
				++genesis.nNonce;
				if (genesis.nNonce == 0)
				{
					printf("NONCE WRAPPED, incrementing time\n");
					++genesis.nTime;
				}
			}
			printf("genesis.nTime = %u \n", genesis.nTime);
			printf("genesis.nNonce = %u \n", genesis.nNonce);
			printf("genesis.nVersion = %u \n", genesis.nVersion);
			printf("genesis.GetHash = 0x%s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
			printf("genesis.hashMerkleRoot = 0x%s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root/
		}
        assert(hashGenesisBlock == uint256("0x00000bb4674a7aea871240253ddeaf3efe72668d252c4d8b4583bb150f8e39b4"));
        assert(genesis.hashMerkleRoot == uint256("0xad426dc7e446a007bef252f05a8097733ebcbae7fce8a61b6980ad79718f7bdd"));

        vSeeds.push_back(CDNSSeedData("www.superskynet.org", "www.superskynet.org"));
	    vSeeds.push_back(CDNSSeedData("47.52.45.101", "47.52.45.101"));
	    vSeeds.push_back(CDNSSeedData("139.196.19.127", "139.196.19.127"));
        

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 50000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xc1;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        vAlertPubKey = ParseHex("048146f47ad5dc7c1d0e7e17cab37b210ca835a79f5de115bf4060786a65cc3e4986b100e19ae4adb61350a5ed884d4b8b8169442b84903ceff968a6620e56720c");
        nDefaultPort = 11203;
        nRPCPort = 11204;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1315189;
        hashGenesisBlock = genesis.GetHash();	
        // Modify the testnet genesis block so the timestamp is valid for a later start.
        assert(hashGenesisBlock == uint256("0x00000bb4674a7aea871240253ddeaf3efe72668d252c4d8b4583bb150f8e39b4"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 50000;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xb5;
        pchMessageStart[2] = 0xbf;
        pchMessageStart[3] = 0xda;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        genesis.nTime = 1504081800;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1315189;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 11205;
        strDataDir = "regtest";
       
        assert(hashGenesisBlock == uint256("0x00000bb4674a7aea871240253ddeaf3efe72668d252c4d8b4583bb150f8e39b4"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
