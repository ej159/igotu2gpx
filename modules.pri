# Use clebsModule(module,deps) to add a module if certain dependencies are
# available, disable modules in CLEBS_DISABLED

clebsModule(marblevisualizer,libmarble)
clebsModule(libusbconnection,libusb)
clebsModule(libusb10connection,libusb10)
clebsModule(serialconnection)
