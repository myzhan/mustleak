# mustleak
**Mustleak** is a `LD_PRELOAD` based utility that leaks memory predictably.

By simulating memory leaks in a process, we can test OOMKiller and eviction in kubernetes.

# Features
- Use LD_PRELOAD on Linux and DYLD_INSERT_LIBRARIES on MacOS.
- Configuration via environment variables.

# Build
```bash
make
```

# Test
```basd
# Linux
make test-linux
# MacOS
make test-darwin
```

# Usage
```bash
# Linux
LD_PRELOAD=./libmustleak.so ./testprog
# MacOS
DYLD_INSERT_LIBRARIES=./libmustleak.so ./testprog
```

# Configuration
Mustleak is configuable via environment variables.

| Name | Type | Default Value | Comment |
| ------------- | ------------- | ------------- | ------------- |
| MUSTLEAK_DEBUG | int | 0 | Changing to 1 will enable debug log |
| MUSTLEAK_MB_PER_SEC | int | 1 | Number of MB data leaking per second |
| MUSTLEAK_STOP_COUNT | int | 100 | How many times will leaking stop |