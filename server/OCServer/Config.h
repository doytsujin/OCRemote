#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <unordered_map>
#include <vector>
#include <string>
#include "Storages.h"

namespace Config {
  struct Client {
    std::string name;
    bool sendLog, verticalScreen;
  };

  struct Filter {
    std::string label, name;
    SharedItemFilter build();
  };

  struct Storage {
    virtual ~Storage() = default;
    virtual ::UniqueStorage build() = 0;
  };
  using UniqueStorage = std::unique_ptr<Storage>;

  struct StorageChest : Storage {
    std::vector<AccessInv> accesses;
    ::UniqueStorage build() override;
  };

  struct StorageME : Storage {
    std::vector<AccessME> accesses;
    ::UniqueStorage build() override;
  };

  struct StorageDrawer : Storage {
    std::vector<AccessInv> accesses;
    std::vector<Filter> filters;
    ::UniqueStorage build() override;
  };

  struct Backup {
    Filter filter;
    int qty;
  };

  struct Process {
    virtual ~Process() = default;
    virtual ::UniqueProcess build() = 0;
  };
  using UniqueProcess = std::unique_ptr<Process>;

  struct Factory {
    std::string name;
    int minCycleTime;
    std::unordered_map<std::string, Client> clients;
    std::vector<UniqueStorage> storages;
    std::vector<Backup> backups;
    std::vector<UniqueProcess> processes;
    // TODO: processes
    UniqueFactory build(Server &s);
  };
}

#endif
