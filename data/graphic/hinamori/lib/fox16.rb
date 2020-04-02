begin
  require 'hin16_c'
rescue LoadError
  # If it's a Windows binary gem, try the <major>.<minor> subdirectory
  if RUBY_PLATFORM =~/(mswin|mingw)/i
    major_minor = RUBY_VERSION[ /^(\d+\.\d+)/ ] or
      raise "Oops, can't extract the major/minor version from #{RUBY_VERSION.dump}"

    add_dll_path = proc do |path, &block|
      begin
        require 'ruby_installer/runtime'
        RubyInstaller::Runtime.add_dll_directory(path, &block)
      rescue LoadError
        old_path = ENV['PATH']
        ENV['PATH'] = "#{path};#{old_path}"
        block.call
        ENV['PATH'] = old_path
      end
    end

    # Temporary add this directory for DLL search, so that bundled DLLs can be found.
    ports_dir = RbConfig::CONFIG["host"].gsub('i686-pc-mingw32') do
      major_minor < '2.0' ? 'i586-mingw32msvc' : 'i686-w64-mingw32'
    end
    ports_bin = File.expand_path("../../ports/#{ports_dir}/bin", __FILE__)
    add_dll_path.call(ports_bin) do
      require "#{major_minor}/hin16_c"
    end
  else
    raise
  end
end

require "hin16/core"
require "hin16/dict"
require "hin16/settings"
require "hin16/iterators"
require "hin16/keys"
require "hin16/aliases"
require "hin16/responder2"
require "hin16/glgroup"
require "hin16/execute_nonmodal"
require "hin16/version"
require "hin16/kwargs"
require "hin16/exceptions_for_fxerror"
require "hin16/thread"
