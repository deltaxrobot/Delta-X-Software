TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += fixture fixture_v3 test
fixture.file = $$PWD/fixture/fixture.pro
fixture_v3.file = $$PWD/fixture_v3/fixture_v3.pro
test.file = $$PWD/test/test.pro
test.depends = fixture fixture_v3
