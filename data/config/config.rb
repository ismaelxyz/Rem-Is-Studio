#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

require_relative '../utilities/utilities'

class Idiom
end

class Config

    def initialize()
        @data_config_app = {}
        @data_config_user = {}
        
        # @info_user: Internal Use Only, not doc.
        @info_user = {'Name' => ENV['USER'], 'Idiom' => 'en', 
                      'ActivateLog' => nil, 'Update' => nil,
                      'ReportError' => nil, 'Mode' => nil}
    end

    def app()
        # Read attribute app.
        return @data_config_app.clone()
    end

    def user()
        # Read attribute user.
        return @data_config_user.clone()
    end

    def load_all()
        load_all_user()
        load_all_app()
    end

    def load_all_user()
        load_dir_user()
        load_dir_config_user()
        load_default_config_user() # preestablecida <-defecto
    end

    def load_all_app()
        load_dir_run()
        load_dir_config_app()
        load_default_config_app()
        load_extensions_dir()
    end

    def load_dir_user()
        @data_config_user.update('DirUser' => Dir.home())
    end

    def load_dir_config_user()
        @data_config_user.update('DirConfig' => Dir.home() + '/.RIS/config')
    end

    def load_dir_config_app()
        @data_config_app.update('DirConfig' => "#{RFile.dirname($0)}/data/config")
    end

    def load_default_config_user()
        # Force, load config User and sync data
        # fc = file of config
        force_path("#{@data_config_user['DirConfig']}/config.yml" => 'f')
        data = read_yaml("#{@data_config_user['DirConfig']}/config.yml")

        @info_user.each{|info|
            @data_config_user[info[0]] = info[1]
            edit_config({info[0] => info[1]}, 'u') unless data.include?(info[0])
        }
    end

    def load_default_config_app()
        @data_config_app.update(read_yaml("#{@data_config_app['DirConfig']}/config.yml"))
    end

    def load_extensions_dir()
        @data_config_app.update('ExtensionsDir' => "#{RFile.dirname($0)}/data/extensions")
    end

    def load_dir_run()
        # Carpeta donde se ejecuta este programa
        @data_config_app.update('BaseDir' => RFile.dirname($0))
    end

    def self.see_config_data(command, *data)
        
        if command == 'u'
            command = "#{Dir.home()}/.RIS/config/config.yml"
            
        elsif command == 'a'
            command = "#{RFile.dirname($0)}/data/config/config.yml"
        else
            #"Unknown command: #{command}"
            return []
        end
        return data.map{|d| read_yaml(command)[d]}
    end

    def edit_config(data, command)
        command = "#{@data_config_user['DirConfig']}/config.yml" if command == 'u'
        command = "#{@data_config_app['DirConfig']}/config.yml" if command == 'a'
        #d = "Not save changes-> given: #{data.class}, expected: Hash.\n"
        return write_yaml(command, data) if data.is_a?(Hash)
    end
end

class Idiom
    
    attr_reader :data_package

    def initialize(extensions_dir, pack = '/en/en.yml')
        @lan_dir = "#{extensions_dir}/idioms"
        @pack = @lan_dir + pack
        update_lan()
    end

    def update_lan()
        @data_package = read_yaml(@pack)
        @idiom = @data_package['words']
        @data_package.delete('words')
    end

    def translate(*text)
        text_f = []
        text.map.with_index{|t, n|
            if t.is_a?(Array)
                t = translate(*t)
                t = [t] if t.is_a?(String)
                text_f.append(t)
            elsif t.is_a?(String)
                if t.include?(' ')
                    t = translate(*t.split(' '))
                    t = t.join(' ') if t.is_a?(Array)
                end
                text_f[n - 1] += make_translate(t[1..]) if t[0] == '/'
                text_f.append(make_translate(t)) if t[0] != '/'
            else
                text_f.append(t)
            end
        }
        text_f = text_f[0] if text_f.size() == 1
        return text_f
    end

    def make_translate(word)
        return @idiom[word] || word
    end

    protected :make_translate
end
__END__
asd = Config.new()
asd.load_all_user()
asd.load_all_app()
print(asd.data_config_app(), "\n", asd.data_config_user())
#print(read_yaml('C:/Users/juan/Documents/Ismael/Proyectos/Rem-Is-Studio-unstable/data/config/config.yml'))

MainLanguage: en
PathDataApp: 'other'
FileRunPath: 'other'