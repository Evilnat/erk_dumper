cd payload
make clean && make all
../bin2c -o "../source/payload.shellcode.inc" payload.bin
cd ..
cd source
make clean && make all
cd ..
scetool --sce-type=SELF --key-revision=01 --self-auth-id=1010000001000003 --self-vendor-id=01000002 --self-type=NPDRM --self-fw-version=0004008000000000 --self-app-version=0001000000000000 --self-ctrl-flags=4000000000000000000000000000000000000000000000000000000000000002 --self-cap-flags=00000000000000000000000000000000000000000000003B0000000100002000 --np-license-type=FREE --np-app-type=EXEC --np-content-id=UP0001-FLTZ00010_00-ERKDUMPER0000000 --np-real-fname=EBOOT.BIN --compress-data=TRUE --encrypt "source\EBOOT.ELF" "pkg\USRDIR\EBOOT.BIN"
cd pkg && psn_package_npdrm