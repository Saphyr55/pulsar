#include <cstdlib>

#include <defines.hpp>
#include <memory/memory.hpp>
#include <memory/memory_trace.hpp>
#include <collection/array.hpp>
#include <collection/index_range.hpp>
#include <collection/option.hpp>
#include <io/console.hpp>
#include <io/file_handle.hpp>
#include <io/file_system.hpp>
#include <memory/shared_ref.hpp>

using namespace pulsar;

struct Player {
    int8_t health_point;
    int8_t attack_point;
};

static Option<Player> DeserializePlayer(StringRef filepath) {
    FileSystem& file_system = FileSystem::GetPlatformFileSystem();
	
    FileOpenError<SharedRef<FileHandle>> stream_res = file_system.OpenRead(filepath);
    if (!stream_res.HasValue()) {
        return Option<Player>::None();
    }

    SharedRef<FileHandle> stream = stream_res.Value();

    Array<uint8_t> buffer(sizeof(Player));
    if (!stream->Read(buffer.Data(), sizeof(Player))) {
        return Option<Player>::None();
    }

    Player player(0, 0);

    Memory::Copy(reinterpret_cast<void*>(&player),
                 static_cast<void*>(buffer.Data()), sizeof(Player));

    return Option<Player>::Some(player);
}

static void SerializePlayer(StringRef filepath, const Player& player) {
    FileSystem& file_system = FileSystem::GetPlatformFileSystem();

    FileOpenError<SharedRef<FileHandle>> stream_res = file_system.OpenWrite(filepath);
    PCHECK(stream_res.HasValue())

    SharedRef<FileHandle> stream = stream_res.Value();

    Array<uint8_t> buffer(sizeof(Player));

    Memory::Copy(static_cast<void*>(buffer.Data()),
                 reinterpret_cast<void*>(const_cast<Player*>(&player)),
                 sizeof(Player));

    PCHECK(stream->Write(buffer.Data(), sizeof(Player)));
    stream->Flush();
}

int main(int argc, char** argv) {

    Console::WriteLine("Program start.");

    StringRef filepath = "player.bin";

    SerializePlayer(filepath, Player(40, 20));

    Option<Player> player_opt = DeserializePlayer(filepath);
    PCHECK(player_opt.HasValue())

    Player& player = *player_opt;
    
    Console::Writef("Player(health_point=%d, AttackPoint=%d)\n",
                    player.health_point, player.attack_point);

    Console::WriteLine("Program end.");

    return EXIT_SUCCESS;
}
