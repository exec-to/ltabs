#pragma once
#include <QtCore>
#include <QSettings>

class cfg {
    private:
        static QSettings *settings;

    public:

        static     void  Init( )                               { cfg::settings = new QSettings();             }

        static QVariant  read( QString key, QVariant def_val ) { return cfg::settings->value( key, def_val ); }

        static     void write( QString key, QVariant val )     { cfg::settings->setValue( key, val );         }


    class  MainWindow {
        public:
            static QString      getKey( QString k ) { return MainWindow() + "/" + k;  }
          operator QString            ( ) { return "MainWindow"; }

            static QString        edge( ) { return read( getKey( "edge"        ), "right"       ).toString(); }
            static     int       width( ) { return read( getKey( "width"       ), 200           ).toInt   (); }
            static     int button_size( ) { return read( getKey( "button_size" ), 36            ).toInt   (); }

            static    void        edge( const QVariant &val ) { write( getKey(    "edge"        ), val     ); }
            static    void       width( const QVariant &val ) { write( getKey(    "width"       ), val     ); }
            static    void button_size( const QVariant &val ) { write( getKey(    "button_size" ), val     ); }
    };


    class Application {
        public:
            static QString      getKey( QString k ) { return Application() + "/" + k; }
          operator QString            ( ) { return "Application"; }

            static QString  plugin_dir( ) { return read( getKey( "plugin_dir"  ), "plugins"     ).toString(); }
            static QString   theme_dir( ) { return read( getKey( "theme_dir"   ), "themes"      ).toString(); }
            static QString       theme( ) { return read( getKey( "theme"       ), "default.qss" ).toString(); }
            static QString   icons_set( ) { return read( getKey( "icons_set"   ), "dark"        ).toString(); }

            static    void  plugin_dir( const QVariant &val ) { write( getKey(    "plugin_dir"  ), val     ); }
            static    void   theme_dir( const QVariant &val ) { write( getKey(    "theme_dir"   ), val     ); }
            static    void       theme( const QVariant &val ) { write( getKey(    "theme"       ), val     ); }
            static    void   icons_set( const QVariant &val ) { write( getKey(    "icons_set"   ), val     ); }
    };


    class Environment {
        public:
            static QString      getKey( QString k ) { return Environment() + "/" + k; }
          operator QString            ( ) { return "Environment"; }

            static     int     is_dock( ) { return read( getKey( "is_dock"     ), 2             ).toInt   (); }
            static     int      dt_num( ) { return read( getKey( "dt_num"      ), 1             ).toInt   (); }
            static     int      screen( ) { return read( getKey( "screen"      ), 0             ).toInt   (); }
            static     int      def_dt( ) { return read( getKey( "def_dt"      ), 0             ).toInt   (); }

            static    void     is_dock( const QVariant &val ) { write( getKey(    "is_dock"     ), val     ); }
            static    void      dt_num( const QVariant &val ) { write( getKey(    "dt_num"      ), val     ); }
            static    void      screen( const QVariant &val ) { write( getKey(    "screen"      ), val     ); }
            static    void      def_dt( const QVariant &val ) { write( getKey(    "def_dt"      ), val     ); }
    };


    class Plugins     {
        public:
            static QString      getKey( QString k ) { return k; }
          operator QString            ( ) { return "Plugins";   }

            static QString        uuid( ) { return read( getKey( "uuid"        ), QVariant()    ).toString(); }
            static QString   file_name( ) { return read( getKey( "file_name"   ), QVariant()    ).toString(); }

            static    void        uuid( const QVariant &val ) { write( getKey(    "uuid"        ), val     ); }
            static    void   file_name( const QVariant &val ) { write( getKey(    "file_name"   ), val     ); }
    };
};
