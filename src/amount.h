// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SYSCOIN_AMOUNT_H
#define SYSCOIN_AMOUNT_H

#include <stdint.h>
#include <limits>
#include <unordered_map>
// SYSCOIN
#include <uint256.h>
/** Amount in satoshis (Can be negative) */
typedef int64_t CAmount;

static const CAmount COIN = 100000000;

/** No amount larger than this (in satoshi) is valid.
 *
 * Note that this constant is *not* the total money supply, which in Syscoin
 * currently happens to be less than 888,000,000 SYS for various reasons, but
 * rather a sanity check. As this sanity check is used by consensus-critical
 * validation code, the exact value of the MAX_MONEY constant is consensus
 * critical; in unusual circumstances like a(nother) overflow bug that allowed
 * for the creation of coins out of thin air modification could lead to a fork.
 * */
static const CAmount MAX_MONEY = 888000000 * COIN;
// SYSCOIN
static const CAmount MAX_ASSET = 1000000000000000000LL - 1LL; // 10^18 - 1 max decimal value that will fit in CAmount
static const CAmount COST_ASSET = 150 * COIN;
inline bool MoneyRange(const CAmount& nValue) { return (nValue >= 0 && nValue <= MAX_MONEY); }
inline bool MoneyRangeAsset(const CAmount& nValue) { return (nValue >= 0 && nValue <= MAX_ASSET); }
struct AssetMapOutput {
    bool bZeroVal;
    // satoshi amount of all outputs
    CAmount nAmount;
    // mapping of NFT ID and the satoshi amount of the output, equivalence will include all input amounts == all output amount && NFT ID amount input == NFT ID amount output for every NFT
    std::unordered_map<uint32_t, CAmount> mapNFTID;
    AssetMapOutput(const bool &bZeroValIn, const CAmount &nAmountIn, const std::unordered_map<uint32_t, CAmount> &mapNFTIDIn): bZeroVal(bZeroValIn), nAmount(nAmountIn), mapNFTID(mapNFTIDIn) {}
    // this is consensus critical, it will ensure input assets and output assets are equal
    friend bool operator==(const AssetMapOutput& a, const AssetMapOutput& b)
    {
        return (a.bZeroVal == b.bZeroVal &&
                a.nAmount  == b.nAmount &&
                a.mapNFTID == b.mapNFTID);
    }

    friend bool operator!=(const AssetMapOutput& a, const AssetMapOutput& b)
    {
        return !(a == b);
    }
};
typedef std::unordered_map<uint32_t, AssetMapOutput> CAssetsMap;
#endif //  SYSCOIN_AMOUNT_H
