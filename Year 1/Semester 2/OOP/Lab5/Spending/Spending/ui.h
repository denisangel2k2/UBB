#pragma once

typedef struct {
    service* srv;
}ui_type;

ui_type* create_ui(service* srv);
void delete_ui(ui_type* ui);
void ui_run(ui_type* ui);