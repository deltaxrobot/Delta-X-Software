TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += fixture fixture_v3 block_programming_plugin test
fixture.file = $$PWD/fixture/fixture.pro
fixture_v3.file = $$PWD/fixture_v3/fixture_v3.pro
block_programming_plugin.file = $$PWD/block_programming_plugin/block_programming_plugin.pro
test.file = $$PWD/test/test.pro
test.depends = fixture fixture_v3 block_programming_plugin
