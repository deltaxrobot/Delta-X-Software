TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += fixture test
fixture.file = $$PWD/fixture/fixture.pro
test.file = $$PWD/test/test.pro
test.depends = fixture
