#ifndef EOL_SETTINGS
#define EOL_SETTINGS

enum class MapAlignment { None, Left, Middle, Right };
enum class RendererType { Software, OpenGL };

constexpr double MIN_ZOOM = 0.25;
constexpr double MAX_ZOOM = 2.00;

struct eol_settings {
    eol_settings();
    static void read_settings();
    static void write_settings();

    int screen_width;
    int screen_height;
    bool pictures_in_background;
    bool center_camera;
    bool center_map;
    MapAlignment map_alignment;

  private:
    double zoom_;

  public:
    bool zoom_textures;
    RendererType renderer;

    int alovolt_P1;

    double zoom() const { return zoom_; }
    void set_zoom(double z);
};

extern eol_settings* EolSettings;

#endif
