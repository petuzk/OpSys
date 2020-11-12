# Sprawozdanie do zadania 6

## Przeanalizuj wykonanie się programu wyświetlającego napis "Hello world" na ekranie

```
$ strace ./hello-world
# Podmieniamy proces (po forku z basha)
execve("./hello-world", ["./hello-world"], [/* 23 vars */]) = 0
# Wchodzimy w entry point, ładujemy do pamięci biblioteki dynamiczne
brk(NULL)                               = 0x1898000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=26041, ...}) = 0
mmap(NULL, 26041, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f524e322000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0`\t\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1868984, ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f524e321000
mmap(NULL, 3971488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f524dd3a000
mprotect(0x7f524defa000, 2097152, PROT_NONE) = 0
mmap(0x7f524e0fa000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c0000) = 0x7f524e0fa000
mmap(0x7f524e100000, 14752, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f524e100000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f524e320000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f524e31f000
arch_prctl(ARCH_SET_FS, 0x7f524e320700) = 0
mprotect(0x7f524e0fa000, 16384, PROT_READ) = 0
mprotect(0x600000, 4096, PROT_READ)     = 0
mprotect(0x7f524e329000, 4096, PROT_READ) = 0
munmap(0x7f524e322000, 26041)           = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
brk(NULL)                               = 0x1898000
brk(0x18b9000)                          = 0x18b9000
# Wchodzimy do main, który wyświetla napis
write(1, "Hello, world!\n", 14)         = 14
# Napis pojawia się w konsoli
Hello, world!
# Kończymy pracę
exit_group(0)                           = ?
+++ exited with 0 +++
```

## Wykorzystaj program strace do znalezienia wszystkich plików konfiguracyjnych, jakie powłoka próbuje odczytać przy starcie

Polecenie niżej wywołuje bash w trybie interaktywnym (`bash -i`), `strace` przekierowuje wyjście do `grep '"/'` (`strace -o "| grep '\"/'"`).

```
$ strace -o "| grep '\"/'" bash -i
execve("/bin/bash", ["bash", "-i"], [/* 23 vars */]) = 0
# Ładowanie bibliotek dynamicznych wycięto
open("/etc/passwd", O_RDONLY|O_CLOEXEC) = 3
stat("/vagrant/Lab 4", {st_mode=S_IFDIR|0755, st_size=352, ...}) = 0
open("/usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache", O_RDONLY) = 3
stat("/home/vagrant/bin/bash", 0x7ffebab84810) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/bash", 0x7ffebab84810) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/bash", 0x7ffebab84810) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/bash", 0x7ffebab84810) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/bash", 0x7ffebab84810)  = -1 ENOENT (No such file or directory)
stat("/usr/bin/bash", 0x7ffebab84810)   = -1 ENOENT (No such file or directory)
stat("/sbin/bash", 0x7ffebab84810)      = -1 ENOENT (No such file or directory)
stat("/bin/bash", {st_mode=S_IFREG|0755, st_size=1037528, ...}) = 0
stat("/bin/bash", {st_mode=S_IFREG|0755, st_size=1037528, ...}) = 0
access("/bin/bash", X_OK)               = 0
stat("/bin/bash", {st_mode=S_IFREG|0755, st_size=1037528, ...}) = 0
access("/bin/bash", R_OK)               = 0
stat("/bin/bash", {st_mode=S_IFREG|0755, st_size=1037528, ...}) = 0
stat("/bin/bash", {st_mode=S_IFREG|0755, st_size=1037528, ...}) = 0
access("/bin/bash", X_OK)               = 0
stat("/bin/bash", {st_mode=S_IFREG|0755, st_size=1037528, ...}) = 0
access("/bin/bash", R_OK)               = 0
open("/etc/bash.bashrc", O_RDONLY)      = 3
faccessat(AT_FDCWD, "/etc/debian_chroot", R_OK) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.sudo_as_admin_successful", 0x7ffebab84370) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.hushlogin", 0x7ffebab84370) = -1 ENOENT (No such file or directory)
faccessat(AT_FDCWD, "/usr/lib/command-not-found", X_OK) = 0
faccessat(AT_FDCWD, "/usr/share/command-not-found/command-not-found", X_OK) = -1 ENOENT (No such file or directory)
open("/home/vagrant/.bashrc", O_RDONLY) = 3
open("/home/vagrant/.bash_history", O_RDONLY) = 3
faccessat(AT_FDCWD, "/usr/bin/lesspipe", X_OK) = 0
faccessat(AT_FDCWD, "/etc/debian_chroot", R_OK) = -1 ENOENT (No such file or directory)
faccessat(AT_FDCWD, "/usr/bin/dircolors", X_OK) = 0
faccessat(AT_FDCWD, "/home/vagrant/.dircolors", R_OK) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.bash_aliases", 0x7ffebab84480) = -1 ENOENT (No such file or directory)
stat("/usr/share/bash-completion/bash_completion", {st_mode=S_IFREG|0644, st_size=67661, ...}) = 0
open("/usr/share/bash-completion/bash_completion", O_RDONLY) = 3
stat("/etc/rc.d/init.d", 0x7ffebab838f0) = -1 ENOENT (No such file or directory)
stat("/etc/init.d", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
stat("/etc/slackware-version", 0x7ffebab83af0) = -1 ENOENT (No such file or directory)
open("/etc/init.d/", O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_CLOEXEC) = 3
# Ta komenda jest wywoływana dla każdego pliku w /etc/init.d, resztę wycięto
faccessat(AT_FDCWD, "/etc/init.d/acpid", X_OK) = 0
stat("/etc/bash_completion.d", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
faccessat(AT_FDCWD, "/etc/bash_completion.d", R_OK) = 0
faccessat(AT_FDCWD, "/etc/bash_completion.d", X_OK) = 0
stat("/etc/bash_completion.d/apport_completion", {st_mode=S_IFREG|0644, st_size=6636, ...}) = 0
faccessat(AT_FDCWD, "/etc/bash_completion.d/apport_completion", R_OK) = 0
open("/etc/bash_completion.d/apport_completion", O_RDONLY) = 3
stat("/etc/bash_completion.d/cloud-init", {st_mode=S_IFREG|0644, st_size=2748, ...}) = 0
faccessat(AT_FDCWD, "/etc/bash_completion.d/cloud-init", R_OK) = 0
open("/etc/bash_completion.d/cloud-init", O_RDONLY) = 3
stat("/etc/bash_completion.d/cryptdisks", {st_mode=S_IFREG|0644, st_size=408, ...}) = 0
faccessat(AT_FDCWD, "/etc/bash_completion.d/cryptdisks", R_OK) = 0
open("/etc/bash_completion.d/cryptdisks", O_RDONLY) = 3
stat("/etc/bash_completion.d/git-prompt", {st_mode=S_IFREG|0644, st_size=439, ...}) = 0
faccessat(AT_FDCWD, "/etc/bash_completion.d/git-prompt", R_OK) = 0
open("/etc/bash_completion.d/git-prompt", O_RDONLY) = 3
stat("/usr/lib/git-core/git-sh-prompt", {st_mode=S_IFREG|0644, st_size=16102, ...}) = 0
open("/usr/lib/git-core/git-sh-prompt", O_RDONLY) = 3
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/etc/bash_completion.d/grub", {st_mode=S_IFREG|0644, st_size=11144, ...}) = 0
faccessat(AT_FDCWD, "/etc/bash_completion.d/grub", R_OK) = 0
open("/etc/bash_completion.d/grub", O_RDONLY) = 3
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-set-default", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-set-default", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-set-default", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-set-default", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-set-default", {st_mode=S_IFREG|0755, st_size=832, ...}) = 0
stat("/usr/sbin/grub-set-default", {st_mode=S_IFREG|0755, st_size=832, ...}) = 0
access("/usr/sbin/grub-set-default", X_OK) = 0
stat("/usr/sbin/grub-set-default", {st_mode=S_IFREG|0755, st_size=832, ...}) = 0
access("/usr/sbin/grub-set-default", R_OK) = 0
stat("/usr/sbin/grub-set-default", {st_mode=S_IFREG|0755, st_size=832, ...}) = 0
stat("/usr/sbin/grub-set-default", {st_mode=S_IFREG|0755, st_size=832, ...}) = 0
access("/usr/sbin/grub-set-default", X_OK) = 0
stat("/usr/sbin/grub-set-default", {st_mode=S_IFREG|0755, st_size=832, ...}) = 0
access("/usr/sbin/grub-set-default", R_OK) = 0
# Ładowanie lokali
open("/usr/share/locale/locale.alias", O_RDONLY|O_CLOEXEC) = 3
open("/usr/share/locale/pl_PL.UTF-8/LC_MESSAGES/bash.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale/pl_PL.utf8/LC_MESSAGES/bash.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale/pl_PL/LC_MESSAGES/bash.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale/pl.UTF-8/LC_MESSAGES/bash.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale/pl.utf8/LC_MESSAGES/bash.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale/pl/LC_MESSAGES/bash.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale-langpack/pl_PL.UTF-8/LC_MESSAGES/bash.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale-langpack/pl_PL.utf8/LC_MESSAGES/bash.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale-langpack/pl_PL/LC_MESSAGES/bash.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale-langpack/pl.UTF-8/LC_MESSAGES/bash.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale-langpack/pl.utf8/LC_MESSAGES/bash.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
open("/usr/share/locale-langpack/pl/LC_MESSAGES/bash.mo", O_RDONLY) = 3
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-reboot", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-reboot", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-reboot", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-reboot", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-reboot", {st_mode=S_IFREG|0755, st_size=4114, ...}) = 0
stat("/usr/sbin/grub-reboot", {st_mode=S_IFREG|0755, st_size=4114, ...}) = 0
access("/usr/sbin/grub-reboot", X_OK)   = 0
stat("/usr/sbin/grub-reboot", {st_mode=S_IFREG|0755, st_size=4114, ...}) = 0
access("/usr/sbin/grub-reboot", R_OK)   = 0
stat("/usr/sbin/grub-reboot", {st_mode=S_IFREG|0755, st_size=4114, ...}) = 0
stat("/usr/sbin/grub-reboot", {st_mode=S_IFREG|0755, st_size=4114, ...}) = 0
access("/usr/sbin/grub-reboot", X_OK)   = 0
stat("/usr/sbin/grub-reboot", {st_mode=S_IFREG|0755, st_size=4114, ...}) = 0
access("/usr/sbin/grub-reboot", R_OK)   = 0
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-editenv", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-editenv", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-editenv", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-editenv", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-editenv", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/bin/grub-editenv", {st_mode=S_IFREG|0755, st_size=234272, ...}) = 0
stat("/usr/bin/grub-editenv", {st_mode=S_IFREG|0755, st_size=234272, ...}) = 0
access("/usr/bin/grub-editenv", X_OK)   = 0
stat("/usr/bin/grub-editenv", {st_mode=S_IFREG|0755, st_size=234272, ...}) = 0
access("/usr/bin/grub-editenv", R_OK)   = 0
stat("/usr/bin/grub-editenv", {st_mode=S_IFREG|0755, st_size=234272, ...}) = 0
stat("/usr/bin/grub-editenv", {st_mode=S_IFREG|0755, st_size=234272, ...}) = 0
access("/usr/bin/grub-editenv", X_OK)   = 0
stat("/usr/bin/grub-editenv", {st_mode=S_IFREG|0755, st_size=234272, ...}) = 0
access("/usr/bin/grub-editenv", R_OK)   = 0
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-mkconfig", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-mkconfig", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-mkconfig", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-mkconfig", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-mkconfig", {st_mode=S_IFREG|0755, st_size=8019, ...}) = 0
stat("/usr/sbin/grub-mkconfig", {st_mode=S_IFREG|0755, st_size=8019, ...}) = 0
access("/usr/sbin/grub-mkconfig", X_OK) = 0
stat("/usr/sbin/grub-mkconfig", {st_mode=S_IFREG|0755, st_size=8019, ...}) = 0
access("/usr/sbin/grub-mkconfig", R_OK) = 0
stat("/usr/sbin/grub-mkconfig", {st_mode=S_IFREG|0755, st_size=8019, ...}) = 0
stat("/usr/sbin/grub-mkconfig", {st_mode=S_IFREG|0755, st_size=8019, ...}) = 0
access("/usr/sbin/grub-mkconfig", X_OK) = 0
stat("/usr/sbin/grub-mkconfig", {st_mode=S_IFREG|0755, st_size=8019, ...}) = 0
access("/usr/sbin/grub-mkconfig", R_OK) = 0
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-bios-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-bios-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-bios-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-bios-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-bios-setup", {st_mode=S_IFREG|0755, st_size=784368, ...}) = 0
stat("/usr/sbin/grub-bios-setup", {st_mode=S_IFREG|0755, st_size=784368, ...}) = 0
access("/usr/sbin/grub-bios-setup", X_OK) = 0
stat("/usr/sbin/grub-bios-setup", {st_mode=S_IFREG|0755, st_size=784368, ...}) = 0
access("/usr/sbin/grub-bios-setup", R_OK) = 0
stat("/usr/sbin/grub-bios-setup", {st_mode=S_IFREG|0755, st_size=784368, ...}) = 0
stat("/usr/sbin/grub-bios-setup", {st_mode=S_IFREG|0755, st_size=784368, ...}) = 0
access("/usr/sbin/grub-bios-setup", X_OK) = 0
stat("/usr/sbin/grub-bios-setup", {st_mode=S_IFREG|0755, st_size=784368, ...}) = 0
access("/usr/sbin/grub-bios-setup", R_OK) = 0
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/bin/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/sbin/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/bin/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/games/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/games/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/snap/bin/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/sbin/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-sparc64-setup", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-install", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-install", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-install", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-install", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-install", {st_mode=S_IFREG|0755, st_size=983424, ...}) = 0
stat("/usr/sbin/grub-install", {st_mode=S_IFREG|0755, st_size=983424, ...}) = 0
access("/usr/sbin/grub-install", X_OK)  = 0
stat("/usr/sbin/grub-install", {st_mode=S_IFREG|0755, st_size=983424, ...}) = 0
access("/usr/sbin/grub-install", R_OK)  = 0
stat("/usr/sbin/grub-install", {st_mode=S_IFREG|0755, st_size=983424, ...}) = 0
stat("/usr/sbin/grub-install", {st_mode=S_IFREG|0755, st_size=983424, ...}) = 0
access("/usr/sbin/grub-install", X_OK)  = 0
stat("/usr/sbin/grub-install", {st_mode=S_IFREG|0755, st_size=983424, ...}) = 0
access("/usr/sbin/grub-install", R_OK)  = 0
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-mkfont", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-mkfont", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-mkfont", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-mkfont", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-mkfont", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/bin/grub-mkfont", {st_mode=S_IFREG|0755, st_size=255264, ...}) = 0
stat("/usr/bin/grub-mkfont", {st_mode=S_IFREG|0755, st_size=255264, ...}) = 0
access("/usr/bin/grub-mkfont", X_OK)    = 0
stat("/usr/bin/grub-mkfont", {st_mode=S_IFREG|0755, st_size=255264, ...}) = 0
access("/usr/bin/grub-mkfont", R_OK)    = 0
stat("/usr/bin/grub-mkfont", {st_mode=S_IFREG|0755, st_size=255264, ...}) = 0
stat("/usr/bin/grub-mkfont", {st_mode=S_IFREG|0755, st_size=255264, ...}) = 0
access("/usr/bin/grub-mkfont", X_OK)    = 0
stat("/usr/bin/grub-mkfont", {st_mode=S_IFREG|0755, st_size=255264, ...}) = 0
access("/usr/bin/grub-mkfont", R_OK)    = 0
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-mkrescue", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-mkrescue", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-mkrescue", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-mkrescue", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-mkrescue", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/bin/grub-mkrescue", {st_mode=S_IFREG|0755, st_size=801824, ...}) = 0
stat("/usr/bin/grub-mkrescue", {st_mode=S_IFREG|0755, st_size=801824, ...}) = 0
access("/usr/bin/grub-mkrescue", X_OK)  = 0
stat("/usr/bin/grub-mkrescue", {st_mode=S_IFREG|0755, st_size=801824, ...}) = 0
access("/usr/bin/grub-mkrescue", R_OK)  = 0
stat("/usr/bin/grub-mkrescue", {st_mode=S_IFREG|0755, st_size=801824, ...}) = 0
stat("/usr/bin/grub-mkrescue", {st_mode=S_IFREG|0755, st_size=801824, ...}) = 0
access("/usr/bin/grub-mkrescue", X_OK)  = 0
stat("/usr/bin/grub-mkrescue", {st_mode=S_IFREG|0755, st_size=801824, ...}) = 0
access("/usr/bin/grub-mkrescue", R_OK)  = 0
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-mkimage", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-mkimage", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-mkimage", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-mkimage", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-mkimage", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/bin/grub-mkimage", {st_mode=S_IFREG|0755, st_size=317120, ...}) = 0
stat("/usr/bin/grub-mkimage", {st_mode=S_IFREG|0755, st_size=317120, ...}) = 0
access("/usr/bin/grub-mkimage", X_OK)   = 0
stat("/usr/bin/grub-mkimage", {st_mode=S_IFREG|0755, st_size=317120, ...}) = 0
access("/usr/bin/grub-mkimage", R_OK)   = 0
stat("/usr/bin/grub-mkimage", {st_mode=S_IFREG|0755, st_size=317120, ...}) = 0
stat("/usr/bin/grub-mkimage", {st_mode=S_IFREG|0755, st_size=317120, ...}) = 0
access("/usr/bin/grub-mkimage", X_OK)   = 0
stat("/usr/bin/grub-mkimage", {st_mode=S_IFREG|0755, st_size=317120, ...}) = 0
access("/usr/bin/grub-mkimage", R_OK)   = 0
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-mkpasswd-pbkdf2", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-mkpasswd-pbkdf2", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-mkpasswd-pbkdf2", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-mkpasswd-pbkdf2", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-mkpasswd-pbkdf2", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/bin/grub-mkpasswd-pbkdf2", {st_mode=S_IFREG|0755, st_size=234472, ...}) = 0
stat("/usr/bin/grub-mkpasswd-pbkdf2", {st_mode=S_IFREG|0755, st_size=234472, ...}) = 0
access("/usr/bin/grub-mkpasswd-pbkdf2", X_OK) = 0
stat("/usr/bin/grub-mkpasswd-pbkdf2", {st_mode=S_IFREG|0755, st_size=234472, ...}) = 0
access("/usr/bin/grub-mkpasswd-pbkdf2", R_OK) = 0
stat("/usr/bin/grub-mkpasswd-pbkdf2", {st_mode=S_IFREG|0755, st_size=234472, ...}) = 0
stat("/usr/bin/grub-mkpasswd-pbkdf2", {st_mode=S_IFREG|0755, st_size=234472, ...}) = 0
access("/usr/bin/grub-mkpasswd-pbkdf2", X_OK) = 0
stat("/usr/bin/grub-mkpasswd-pbkdf2", {st_mode=S_IFREG|0755, st_size=234472, ...}) = 0
access("/usr/bin/grub-mkpasswd-pbkdf2", R_OK) = 0
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-probe", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-probe", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-probe", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-probe", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-probe", {st_mode=S_IFREG|0755, st_size=784304, ...}) = 0
stat("/usr/sbin/grub-probe", {st_mode=S_IFREG|0755, st_size=784304, ...}) = 0
access("/usr/sbin/grub-probe", X_OK)    = 0
stat("/usr/sbin/grub-probe", {st_mode=S_IFREG|0755, st_size=784304, ...}) = 0
access("/usr/sbin/grub-probe", R_OK)    = 0
stat("/usr/sbin/grub-probe", {st_mode=S_IFREG|0755, st_size=784304, ...}) = 0
stat("/usr/sbin/grub-probe", {st_mode=S_IFREG|0755, st_size=784304, ...}) = 0
access("/usr/sbin/grub-probe", X_OK)    = 0
stat("/usr/sbin/grub-probe", {st_mode=S_IFREG|0755, st_size=784304, ...}) = 0
access("/usr/sbin/grub-probe", R_OK)    = 0
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/grub-script-check", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/grub-script-check", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/grub-script-check", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/grub-script-check", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/grub-script-check", 0x7ffebab82bb0) = -1 ENOENT (No such file or directory)
stat("/usr/bin/grub-script-check", {st_mode=S_IFREG|0755, st_size=254408, ...}) = 0
stat("/usr/bin/grub-script-check", {st_mode=S_IFREG|0755, st_size=254408, ...}) = 0
access("/usr/bin/grub-script-check", X_OK) = 0
stat("/usr/bin/grub-script-check", {st_mode=S_IFREG|0755, st_size=254408, ...}) = 0
access("/usr/bin/grub-script-check", R_OK) = 0
stat("/usr/bin/grub-script-check", {st_mode=S_IFREG|0755, st_size=254408, ...}) = 0
stat("/usr/bin/grub-script-check", {st_mode=S_IFREG|0755, st_size=254408, ...}) = 0
access("/usr/bin/grub-script-check", X_OK) = 0
stat("/usr/bin/grub-script-check", {st_mode=S_IFREG|0755, st_size=254408, ...}) = 0
access("/usr/bin/grub-script-check", R_OK) = 0
stat("/etc/bash_completion.d/insserv", {st_mode=S_IFREG|0644, st_size=736, ...}) = 0
faccessat(AT_FDCWD, "/etc/bash_completion.d/insserv", R_OK) = 0
open("/etc/bash_completion.d/insserv", O_RDONLY) = 3
open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
stat("/home/vagrant/bin/insserv", 0x7ffebab82ab0) = -1 ENOENT (No such file or directory)
stat("/home/vagrant/.local/bin/insserv", 0x7ffebab82ab0) = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/insserv", 0x7ffebab82ab0) = -1 ENOENT (No such file or directory)
stat("/usr/local/bin/insserv", 0x7ffebab82ab0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/insserv", 0x7ffebab82ab0) = -1 ENOENT (No such file or directory)
stat("/usr/bin/insserv", 0x7ffebab82ab0) = -1 ENOENT (No such file or directory)
stat("/sbin/insserv", 0x7ffebab82ab0)   = -1 ENOENT (No such file or directory)
stat("/bin/insserv", 0x7ffebab82ab0)    = -1 ENOENT (No such file or directory)
stat("/usr/games/insserv", 0x7ffebab82ab0) = -1 ENOENT (No such file or directory)
stat("/usr/local/games/insserv", 0x7ffebab82ab0) = -1 ENOENT (No such file or directory)
stat("/snap/bin/insserv", 0x7ffebab82ab0) = -1 ENOENT (No such file or directory)
stat("/usr/sbin/insserv", 0x7ffebab82ab0) = -1 ENOENT (No such file or directory)
stat("/sbin/insserv", 0x7ffebab82ab0)   = -1 ENOENT (No such file or directory)
stat("/usr/local/sbin/insserv", 0x7ffebab82ab0) = -1 ENOENT (No such file or directory)
faccessat(AT_FDCWD, "/home/vagrant/.bash_completion", R_OK) = -1 ENOENT (No such file or directory)
open("/home/vagrant/.bash_history", O_RDONLY) = 3
stat("/home/vagrant/.bash_history", {st_mode=S_IFREG|0600, st_size=31824, ...}) = 0
open("/home/vagrant/.bash_history", O_RDONLY) = 3
stat("/home/vagrant/.terminfo", 0x7e5008) = -1 ENOENT (No such file or directory)
stat("/etc/terminfo", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
stat("/lib/terminfo", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
stat("/usr/share/terminfo", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
access("/etc/terminfo/x/xterm-256color", R_OK) = -1 ENOENT (No such file or directory)
access("/lib/terminfo/x/xterm-256color", R_OK) = 0
open("/lib/terminfo/x/xterm-256color", O_RDONLY) = 3
stat("/home/vagrant/.inputrc", 0x7ffebab83a50) = -1 ENOENT (No such file or directory)
stat("/etc/inputrc", {st_mode=S_IFREG|0644, st_size=1748, ...}) = 0
open("/etc/inputrc", O_RDONLY)          = 3
( inner bash )$ exit
exit
```

## Sprawdź czy plik edytowany w programie pico jest stale otwarty

W moim systemie `pico` jest symlinkiem do `nano`.

```
$ strace -o strace.log nano ~/.bashrc
# Otwieram ~/.bashrc w nano, dodaję na samym początku komentarz, zapisuję plik
$ grep -nA 10 .bashrc strace.log
1:execve("/bin/nano", ["nano", "/home/vagrant/.bashrc"], [/* 23 vars */]) = 0
--
409:stat("/home/vagrant/.bashrc", {st_mode=S_IFREG|0644, st_size=3771, ...}) = 0
412:stat("/home/vagrant/..bashrc.swp", 0x7ffedbac72a0) = -1 ENOENT (No such file or directory)
--
# Tutaj nano widocznie tworzy plik, które będzie służył jako kopia zapasowa
482:stat("/home/vagrant/..bashrc.swp", 0x7ffedbac7190) = -1 ENOENT (No such file or directory)
483:open("/home/vagrant/..bashrc.swp", O_WRONLY|O_CREAT|O_EXCL|O_APPEND, 0666) = 3
484-fcntl(3, F_GETFL)                       = 0x8401 (flags O_WRONLY|O_APPEND|O_LARGEFILE)
485-fstat(3, {st_mode=S_IFREG|0664, st_size=0, ...}) = 0
486-write(3, "b0nano 2.5.3\0\0\0\0\0\0\0\0\0\0\0\0\335\f\0\0vagr"..., 1024) = 1024
487-close(3)                                = 0
--
# Otwiera podany plik
493:stat("/home/vagrant/.bashrc", {st_mode=S_IFREG|0644, st_size=3771, ...}) = 0
494:stat("/home/vagrant/.bashrc", {st_mode=S_IFREG|0644, st_size=3771, ...}) = 0
495:open("/home/vagrant/.bashrc", O_RDONLY) = 3
496-fcntl(3, F_GETFL)                       = 0x8000 (flags O_RDONLY|O_LARGEFILE)
--
521:fstat(3, {st_mode=S_IFREG|0644, st_size=3771, ...}) = 0
# Wczytuje plik porcjami 4096 bajtów
522:read(3, "# ~/.bashrc: executed by bash(1)"..., 4096) = 3771
523-read(3, "", 4096)                       = 0
# Zamyka plik dwa razy
524-close(3)                                = 0
525-close(3)                                = -1 EBADF (Bad file descriptor)
--
# Ciągle śledzi zmiany zewnętrzne
531:stat("/home/vagrant/.bashrc", {st_mode=S_IFREG|0644, st_size=3771, ...}) = 0
532:open("/home/vagrant/.bashrc", O_WRONLY|O_CREAT|O_APPEND, 0666) = 3
533-fcntl(3, F_GETFL)                       = 0x8401 (flags O_WRONLY|O_APPEND|O_LARGEFILE)
# Znów zamyka plik dwa razy
534-close(3)                                = 0
535-close(3)                                = -1 EBADF (Bad file descriptor)
--
# Wyświetla informacje dla użytkownika
539-write(1, "\33[32;53H\33(B\33[0;7m[ Wczytano 117 "..., 48) = 48
--
# Zapisuje backup?
575:stat("/home/vagrant/..bashrc.swp", {st_mode=S_IFREG|0664, st_size=1024, ...}) = 0
576:unlink("/home/vagrant/..bashrc.swp")    = 0
577:open("/home/vagrant/..bashrc.swp", O_WRONLY|O_CREAT|O_EXCL|O_APPEND, 0666) = 3
578-fcntl(3, F_GETFL)                       = 0x8401 (flags O_WRONLY|O_APPEND|O_LARGEFILE)
579-fstat(3, {st_mode=S_IFREG|0664, st_size=0, ...}) = 0
580-write(3, "b0nano 2.5.3\0\0\0\0\0\0\0\0\0\0\0\0\335\f\0\0vagr"..., 1024) = 1024
581-close(3)                                = 0
--
# Zapisuje zmiany
662:open("/home/vagrant/.bashrc", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
663-umask(02)                               = 02
664-fcntl(3, F_GETFL)                       = 0x8001 (flags O_WRONLY|O_LARGEFILE)
665-fstat(3, {st_mode=S_IFREG|0644, st_size=0, ...}) = 0
666:write(3, "# Hi\n# ~/.bashrc: executed by ba"..., 3776) = 3776
667-close(3)                                = 0
--
# Usuwa plik swp
679:unlink("/home/vagrant/..bashrc.swp")    = 0
```

## Odczytaj jakie file deskryptory posiada uruchomiona aplikacja wyświetlająca napis Hello world na ekranie

	- `/etc/ld.so.cache`
	- `/lib/x86_64-linux-gnu/libc.so.6`
	- `/dev/pts/0`

```
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3</etc/ld.so.cache>
fstat(3</etc/ld.so.cache>, {st_mode=S_IFREG|0644, st_size=26041, ...}) = 0
mmap(NULL, 26041, PROT_READ, MAP_PRIVATE, 3</etc/ld.so.cache>, 0) = 0x7f945539b000
close(3</etc/ld.so.cache>)              = 0
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3</lib/x86_64-linux-gnu/libc-2.23.so>
read(3</lib/x86_64-linux-gnu/libc-2.23.so>, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0`\t\2\0\0\0\0\0"..., 832) = 832
fstat(3</lib/x86_64-linux-gnu/libc-2.23.so>, {st_mode=S_IFREG|0755, st_size=1868984, ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f945539a000
mmap(NULL, 3971488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3</lib/x86_64-linux-gnu/libc-2.23.so>, 0) = 0x7f9454db3000
mmap(0x7f9455173000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3</lib/x86_64-linux-gnu/libc-2.23.so>, 0x1c0000) = 0x7f9455173000
mmap(0x7f9455179000, 14752, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9455179000
close(3</lib/x86_64-linux-gnu/libc-2.23.so>) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9455399000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9455398000
fstat(1</dev/pts/0>, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
write(1</dev/pts/0>, "Hello, world!\n", 14) = 14
Hello, world!
```
