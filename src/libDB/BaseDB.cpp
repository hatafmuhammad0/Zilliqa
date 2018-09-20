/**
* Copyright (c) 2018 Zilliqa 
* This source code is being disclosed to you solely for the purpose of your participation in 
* testing Zilliqa. You may view, compile and run the code for that purpose and pursuant to 
* the protocols and algorithms that are programmed into, and intended by, the code. You may 
* not do anything else with the code without express permission from Zilliqa Research Pte. Ltd., 
* including modifying or publishing the code (or any part of it), and developing or forming 
* another public or private blockchain network. This source code is provided ‘as is’ and no 
* warranties are given as to title or non-infringement, merchantability or fitness for purpose 
* and, to the extent permitted by law, all liability for your use of the code is disclaimed. 
* Some programs in this code are governed by the GNU General Public License v3.0 (available at 
* https://www.gnu.org/licenses/gpl-3.0.en.html) (‘GPLv3’). The programs that are governed by 
* GPLv3.0 are those programs that are located in the folders src/depends and tests/depends 
* and which include a reference to GPLv3 in their program files.
**/

#include "BaseDB.h"
#include <bsoncxx/stdx/make_unique.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/logger.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

using namespace std;

void BaseDB::Init(unsigned int port)
{
    auto instance = bsoncxx::stdx::make_unique<mongocxx::instance>();
    try
    {

        m_inst = move(instance);
        string uri = "mongodb://localhost:" + to_string(port);
        mongocxx::uri URI(uri);
        mongocxx::client client(URI);
        m_client = move(client);
        m_client[m_dbname].drop();
        m_isInitialized = true;
    }
    catch (exception& e)
    {
        LOG_GENERAL(WARNING, "Failed to initialized DB " << e.what());
    }
}