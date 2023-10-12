// void	iterateContainer();

// void	Config::iterateContainer()
// {
// 	std::string partition(50, '-');
	
// 	std::cout << partition << std::endl;
// 	std::cout << "_confFile\n";
// 	std::cout << partition << std::endl;
// 	for (const auto& outerMap : _confFile) {
//         // Iterate through the outer map
//         for (const auto& outerPair : outerMap) {
//             const std::string& outerKey = outerPair.first;
//             const std::map<std::string, std::vector<std::string> >& innerMap = outerPair.second;

//             // Print outer map key and values
//            std::cout << "Outer Key: " << outerKey << std::endl;

//             // Iterate through the inner map
//             for (const auto& innerPair : innerMap) {
//                 const std::string& innerKey = innerPair.first;
//                 const std::vector<std::string>& innerValue = innerPair.second;

//                 // Print inner map key and values
//                 std::cout << innerKey << std::endl;
//                 std::cout << "Inner Values:" << std::endl;

//                 // Iterate through the inner vector
//                 for (const std::string& value : innerValue) {
//                     std::cout << value << std::endl;
//                 }
//             }
//         }
//     }
// 	std::cout << partition << std::endl;
// 	std::cout << "_globalContext\n";
// 	std::cout << partition << std::endl;
// 	for (const auto& pair : _globalContext) {
// 		const std::string& key = pair.first;
// 		const std::vector<std::string>& values = pair.second;

// 		std::cout << "Key: " << key << std::endl;
// 		std::cout << "Values:" << std::endl;

// 		// Iterate through the vector of values
// 		for (const std::string& value : values) {
// 			std::cout << "  " << value << std::endl;
// 		}
// 	}
// 	std::cout << partition << std::endl;
// 	std::cout << "_loactions\n";
// 	std::cout << partition << std::endl;
// 	for (int i = 0; i < _locations.size(); i++) {
// 		for (int j = 0; j <_locations[i].size(); j++)
// 			std::cout << _locations[i][j] << std::endl;
// 	}
// }

// void	 iterate();

// void	Server::iterate() {
// 	std::cout << "WorkerProcess: " << _workerProcesses << std::endl;
// 	std::cout << "WorkerConnections: "<< _workerConnections << std::endl;
// 	std::cout << "ScriptTimeout: " << _scriptTimeout << std::endl;
// 	std::cout << "ClientTimeout: " << _clientTimeout << std::endl;
// 	std::cout << "BuffSize: " << _buffSize << std::endl;
// 	std::cout << "Backlog: " << _backlog << std::endl;
// 	for (ServerConf& server : _server) {
//         if (!server.locations.empty()) {
// 			std::cout << "Bodysize: " << server.bodySize << std::endl;
//             std::cout << "ServerName: " << server.serverName << std::endl;
//             std::cout << "Port: " << server.port << std::endl;
//             std::cout << "Error Pages:" << std::endl;
//             for (const auto& errorPage : server.errorPages) {
//                 std::cout << "  " << errorPage.first << " -> " << errorPage.second << std::endl;
//             }
//             std::cout << "Locations:" << std::endl;
//             for (const auto& location : server.locations) {
//                     std::cout << "  Location: " << location.first << std::endl;
//                    	const LocationStruc& locStruct = location.second;
//                     std::cout << "    allowGet: " << locStruct.allowGet << std::endl;
//                     std::cout << "    allowPost: " << locStruct.allowPost << std::endl;
//                     std::cout << "    allowDelete: " << locStruct.allowDelete << std::endl;
//                     std::cout << "    autoindex: " << locStruct.autoindex << std::endl;
//                     std::cout << "    root: " << locStruct.root << std::endl;
//                     std::cout << "    index: " << locStruct.index << std::endl;
//                     std::cout << "    Rewrite:" << std::endl;
//                     for (const std::string& rewrite : locStruct.rewrite) {
//                         std::cout << "      " << rewrite << std::endl;
//                     }
//                     std::cout << "    CGI:" << std::endl;
//                     for (const std::string& cgi : locStruct.cgi) {
//                         std::cout << "      " << cgi << std::endl;
//                     }
//                 }
//             std::cout << std::endl;
//         }
//     }
// }

