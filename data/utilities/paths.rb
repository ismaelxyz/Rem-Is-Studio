#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

# REM: Paths

module Utilities

  def file_or_dir(command, path)
    return RFile.file?(path) if command == 'f'  # File
    return RFile.dir?(path) if command == 'd'  #  Dir
    return RFile.exist?(path) if command == 'a' #  All
  end

  def mkdirs(ru)
    # ru = String; example '/home/user'; create path 
    
    [ru].map{|path| path == '/' ? path : path.chomp(?/)}.each{|path|
      begin
        Dir.mkdir(path)
        next
      rescue SystemCallError
        next if RFile.directory?(path)
      end
      
      stack = []
      until path == stack.last()   # dirname('/')=='/', dirname('C:/')=='C:/'
        stack.push(path)
        path = RFile.dirname(path)
      end
      
      stack.pop()    # root directory should exist
      stack.reverse_each{|dir|
        begin
          Dir.mkdir(dir)
        rescue SystemCallError
          raise unless RFile.directory?(dir)
        end
      }
      return ru
    }
    return 'Not created directory: #{ru}.'
  end
   
  def force_path(**path)
    # Create File or Directory.
    # Use: force_path('path'=>'command')
    list_of_forced = [] # lista de forsados 
    path.each{|command|
            
      if command[1] == 'd'
        if not Dir.exist?(command[0])
          mkdirs(command[0])
          list_of_forced.append(false)
          next
        end
        
      elsif command[1] == 'f'
        if not RFile.exist?(command[0])
          mkdirs(RFile.dirname(command[0]))
          f = RFile.open(command[0], 'w')
          f.close()
          list_of_forced.append(false)
          next
        end
      end
      list_of_forced.append(true)
    }
    return list_of_forced
  end

  def rename_path(replace, position=[0, 0], command='f', dir='.')
    # Use: replace[old, new], position[init, end], command[f, d, all]
    position = [position] if position.is_a?(Integer)
    
    Dir.children(dir).each{|path|
      if file_or_dir(command, "%s/%s" % [dir, path])
        if position.is_a?(Array)
          position << 0 if position.size() == 1
          position[1] += replace[0].size() if position[1] == 0
          
          if path[position[0], position[1]] == replace[0]
            name = path.clone()
            name[position[0], position[1]] = replace[1]
            RFile.rename(path, name)
          end
        
        elsif position == 'or' and path.include?(replace[0])
          # or = Only Replace
          RFile.rename(path, path.gsub(replace[0], replace[1]))
        end
      end
    }
  end
end

__END__
# Falta el axeso a force_path
if __FILE__ == $0
  require_relative 'file'
  include Utilities

  unless ARGV.empty?()
    ARGV[0..1] = [[ARGV[0], ARGV[1]]] if ARGV.size() > 1
    ARGV[1..2].each_index{|i|
      ARGV[i+1] = Integer(ARGV[i+1])
    } if ARGV[1] != 'or'
    ARGV[1..] = [[ARGV[1], ARGV[2]]] if ARGV.size() > 2
    rename_path(*ARGV) if ARGV.size() >= 1 
  end
end
# module_function :mkdir_p
# private_module_function :fu_mkdir
# private_methods :mkdirs
# private_methods :mkdirs
  # private_class_method