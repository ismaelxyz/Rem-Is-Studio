SOURCES = *.rb \
        ../lib/hin/calendar.rb \
        ../lib/hin/chore.rb \
        ../lib/hin/core.rb \
        ../lib/hin/glgroup.rb \
        ../lib/hin/glshapes.rb \
        ../lib/hin/input.rb \
        ../lib/hin/iterators.rb \
        ../lib/hin/responder2.rb \
        ../lib/hin/scintilla.rb \
        ../lib/hin/signal.rb \
        ../lib/hin/timeout.rb \
        ../lib/hin/undolist.rb \
        ../lib/hin/version.rb

rdoc:
 @rdoc --op ../doc/api --main README.rdoc $(SOURCES) README.rdoc

ri:
 @rdoc --ri $(SOURCES)

clean:
 @rm -rf ../doc/api
