require 'yaml'

class RFile < File
    # Rem File: File special for Rem.
    def self.append(file, data)
        f = self.open(file, 'a')
        f.write(data)
        f.close()
    end
end

def read_yaml(path_file_yaml)
    # Read a Yaml File.
    return YAML.load(RFile.read(path_file_yaml)) || {}
end

def write_yaml(path_file_yaml, data)
    # Write a Yaml File.
    return RFile.write(path_file_yaml, YAML.dump(read_yaml(path_file_yaml)\
           .update(data)))
end

def mkdirs(ru)
    # ru = String; example '/home/user'; create path  
    return ru if nil

    [ru].map {|path| path == '/' ? path : path.chomp(?/)}.each do |path|
    
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

      stack.pop()               # root directory should exist
      stack.reverse_each do |dir|
        begin
            Dir.mkdir(dir)
        rescue SystemCallError
          raise unless RFile.directory?(dir)
        end
      end

      return ru
    end
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