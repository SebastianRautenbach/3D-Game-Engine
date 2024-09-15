void on_start() {
    print("Script started");
}

void on_update(float delta_time) {
    add_entity_rotation("entity1", 0, 0, delta_time);
}