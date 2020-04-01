#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

require_relative '../utilities/utilities'


class Config
    attr_reader :data_config_app, :data_config_user

    def initialize()
        @data_config_app = {}
        @data_config_user = {}
        

        # @info_user: Internal Use Only, not doc.
        @info_user = {'Name' => nil, 'Language' => 'en', 'ActivateLog' =>nil,
                      'Update' => nil, 'ReportError' => nil, 'Mode' => nil}
    end

    def load_all()
        load_all_user()
        load_all_app()
    end

    def load_all_user()
        load_name_user()
        load_dir_user()
        load_dir_config_user()
        load_default_config_user() # preestablecida <-defecto
    end

    def load_all_app()
        load_dir_run()
        load_dir_config_app()
        load_default_config_app()
    end

    def load_name_user()
        @data_config_user.update('Name' => Dir.home().split('/')[-1])
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
        force_path("#{@data_config_user['DirConfig']}/config.yaml" => 'f')
        data = read_yaml("#{@data_config_user['DirConfig']}/config.yaml")
        @info_user['Name'] = data['Name'] || @data_config_user['Name'] 

        @info_user.each{|info|
            @data_config_user[info[0]] = info[1]
            edit_config({info[0] => info[1]}, 'u') unless data.include?(info[0])
        }
    end

    def load_default_config_app()
        @data_config_app.update(read_yaml("#{@data_config_app['DirConfig']}/config.yaml"))
    end

    def load_dir_run()
        # Carpeta donde se ejecuta este programa
        @data_config_app.update('BaseDir' => RFile.dirname($0))
    end

    def edit_config(data, command)
        command = {
            'u' => "#{@data_config_user['DirConfig']}/config.yaml",
            'a' => "#{@data_config_app['DirConfig']}/config.yaml"
        }[command]
        # data is a Hash.  edit config only for user.
        if data.is_a?(Hash)
            write_yaml(command, data)
        else
            print("AttributeError-> given: #{data.class}, expected: Hash\n")
        end
    end
end

__END__
asd = Config.new()
asd.load_all_user()
asd.load_all_app()
print(asd.data_config_app(), "\n", asd.data_config_user())
#print(read_yaml('C:/Users/juan/Documents/Ismael/Proyectos/Rem-Is-Studio-unstable/data/config/config.yaml'))

MainLanguage: en
PathDataApp: 'other'
FileRunPath: 'other'