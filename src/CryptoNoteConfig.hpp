// Copyright (c) 2012-2018, The CryptoNote developers, The Bytecoin developers.
// Licensed under the GNU Lesser General Public License. See LICENSE for details.

#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include "CryptoNote.hpp"
#include "common/StringTools.hpp"
#include "p2p/P2pProtocolTypes.hpp"

#ifndef CRYPTONOTE_NAME
#error CRYPTONOTE_NAME must be defined before compiling project
#endif

// All values below should only be used in code through Currency and Config classes, never directly.
// This approach allows unlimited customization through config file/command line parameters
// Never include this header into other headers
namespace cn { namespace parameters {

// Magics
const char GENESIS_COINBASE_TX_HEX[] =
    "010a01ff000180c0a8ca9a3a029b2e4c0281c0b02e7c53291a94d1d0cbff8883f8024f5142ee494ffbbd0880712101827b04a29be01f599850ee3fa1140a05bc4292504f0b820f27ca814b0656c7ec";
// Technically, we should not have predefined genesis block, first hard checkpoint is enough. This is bitcoin legacy.
constexpr UUID BYTECOIN_NETWORK = common::pfh<UUID>("00368f56cbba6988783ed50754293f78");  // Bender's nightmare

const Height UPGRADE_HEIGHT_V2                  = 546603;
const Height UPGRADE_HEIGHT_V3                  = 985549;
const Height UPGRADE_HEIGHT_V4                  = 1792117;
const Height KEY_IMAGE_SUBGROUP_CHECKING_HEIGHT = 1267000;

// Radical simplification of consensus rules starts from versions
// Amethyst blocks can contain v1 transactions
const uint8_t BLOCK_VERSION_AMETHYST       = 4;
const uint8_t TRANSACTION_VERSION_AMETHYST = 4;

const size_t MINIMUM_ANONYMITY_AMETHYST = 3;

// Emission and formats
const Amount MONEY_SUPPLY            = 100000000000;
const unsigned EMISSION_SPEED_FACTOR = 18;
static_assert(EMISSION_SPEED_FACTOR > 0 && EMISSION_SPEED_FACTOR <= 8 * sizeof(uint64_t), "Bad EMISSION_SPEED_FACTOR");

const size_t DISPLAY_DECIMAL_POINT = 2;
const Amount MIN_DUST_THRESHOLD    = 1000000;            // Everything smaller will be split in groups of 3 digits
const Amount MAX_DUST_THRESHOLD    = 30000000000000000;  // Everything larger is dust because very few coins
const Amount SELF_DUST_THRESHOLD   = 1000;               // forfeit outputs smaller than this in a change

const uint64_t ADDRESS_BASE58_PREFIX          = 86;       // legacy addresses start with "F"
const uint64_t ADDRESS_BASE58_PREFIX_AMETHYST = 572238;  // addresses start with "bcnZ", varintdata={0xce, 0xf6, 0x22}
const uint64_t SENDPROOF_BASE58_PREFIX        = 86762904402638;
// proofs start with "bcn1PRoof", varintdata={0xce, 0xf5, 0xe2, 0x80, 0x91, 0xdd, 0x13}
const uint64_t VIEWONLYWALLET_BASE58_PREFIX = 3904523549390;
// wallets start with "bcnAUDit", varintdata={0xce, 0xf5, 0xf4, 0xbd, 0xd1, 0x71}
const char BLOCKS_FILENAME[]       = "blocks.bin";
const char BLOCKINDEXES_FILENAME[] = "blockindexes.bin";

// Difficulty and rewards
const Timestamp DIFFICULTY_TARGET              = 120;
const Height EXPECTED_NUMBER_OF_BLOCKS_PER_DAY = 24 * 60 * 60 / DIFFICULTY_TARGET;

const Difficulty MINIMUM_DIFFICULTY_V1 = 1;  // Genesis and some first blocks in main net
const Difficulty MINIMUM_DIFFICULTY    = 100000;

const Height DIFFICULTY_WINDOW = 720;
const Height DIFFICULTY_CUT    = 60;  // out-of-family timestamps to cut after sorting
const Height DIFFICULTY_LAG    = 15;  // skip last blocks for difficulty calcs (against lowering difficulty attack)

static_assert(DIFFICULTY_WINDOW >= 2, "Bad DIFFICULTY_WINDOW");
static_assert(2 * DIFFICULTY_CUT <= DIFFICULTY_WINDOW - 2, "Bad DIFFICULTY_WINDOW or DIFFICULTY_CUT");

// Upgrade voting
const Height UPGRADE_VOTING_PERCENT = 90;
const Height UPGRADE_VOTING_WINDOW  = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;
const Height UPGRADE_WINDOW         = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY * 7;  // Delay after voting
static_assert(60 <= UPGRADE_VOTING_PERCENT && UPGRADE_VOTING_PERCENT <= 100, "Bad UPGRADE_VOTING_PERCENT");
static_assert(UPGRADE_VOTING_WINDOW > 1, "Bad UPGRADE_VOTING_WINDOW");

// Timestamps
const Timestamp BLOCK_FUTURE_TIME_LIMIT             = 60 * 60 * 2;
const Height BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW_V1_3 = 60;
const Height BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW      = 59;
static_assert(BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW % 2 == 1,
    "This window must be uneven for median timestamp to grow monotonically");

// Locking by timestamp and by block
const Height MAX_BLOCK_NUMBER = 500000000;

// Legacy pre amethyst locking constants
const Height LOCKED_TX_ALLOWED_DELTA_BLOCKS = 1;

constexpr Timestamp LOCKED_TX_ALLOWED_DELTA_SECONDS(Timestamp difficulty_target) {
	return difficulty_target * LOCKED_TX_ALLOWED_DELTA_BLOCKS;
}

const Height MINED_MONEY_UNLOCK_WINDOW = 10;

// Size limits
const size_t MAX_HEADER_SIZE         = 2048;
const size_t BLOCK_CAPACITY_VOTE_MIN = 100 * 1000;   // min block size
const size_t BLOCK_CAPACITY_VOTE_MAX = 2000 * 1000;  // max block size
static_assert(BLOCK_CAPACITY_VOTE_MAX >= BLOCK_CAPACITY_VOTE_MIN, "Bad TRANSACTIONS_SIZE_VOTE");
const Height BLOCK_CAPACITY_VOTE_WINDOW = 11;

// Legacy pre amethyst size limits
const size_t MINIMUM_SIZE_MEDIAN_V3 = 100000;
const size_t MINIMUM_SIZE_MEDIAN_V2 = 20000;
const size_t MINIMUM_SIZE_MEDIAN_V1 = 10000;

const Height MEIDAN_BLOCK_SIZE_WINDOW       = 100;
const size_t MAX_BLOCK_SIZE_INITIAL         = 20 * 1024;   // block transactions size
const size_t MAX_BLOCK_SIZE_GROWTH_PER_YEAR = 100 * 1024;  // block transactions size

// P2p ports, not strictly part of consensus
const uint16_t P2P_DEFAULT_PORT        = 18320;
const uint16_t RPC_DEFAULT_PORT        = 18322;
const uint16_t WALLET_RPC_DEFAULT_PORT = 18321;

// We do not want runtime conversion, so compile-time converter
constexpr PublicKey P2P_STAT_TRUSTED_PUBLIC_KEY =
    common::pfh<PublicKey>("E29507CA55455F37A3B783EE2C5123B8B6A34A0C5CAAE050922C6254161480C1");

const PublicKey CHECKPOINT_PUBLIC_KEYS[] = {};

const PublicKey CHECKPOINT_PUBLIC_KEYS_STAGENET[] = {};

const PublicKey CHECKPOINT_PUBLIC_KEYS_TESTNET[] = {};

const char *const SEED_NODES[] = {
    "64.225.77.94:18320"};

const char *const SEED_NODES_STAGENET[] = {
    "207.246.127.160:10080", "108.61.174.232:10080", "45.32.156.183:10080", "45.76.29.96:10080"};
// testnet will have no seed nodes

const HardCheckpoint CHECKPOINTS[] = {};

// When adding checkpoint and BEFORE release, you MUST check that daemon fully syncs both mainnet and stagenet.

// Be extra careful when setting checkpoint around consensus update heights. Follow rules:
// 1. never set checkpoint after or to height where required # of votes for upgrade was gathered
// 2. never set checkpoint before height where upgrade happened (with desired major version)
// 3. after setting checkpoint after upgrade, modify upgrade_heights array

 const HardCheckpoint CHECKPOINTS_STAGENET[] = {};
}}  // namespace cn::parameters
