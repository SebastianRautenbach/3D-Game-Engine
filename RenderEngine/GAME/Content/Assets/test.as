
/*
    I love AngelSript
*/

void on_start() {
    print("Script started");
    //change_mesh("scary", 0, "18410409422620930561");
}

void on_update(float delta_time) {
    add_entity_rotation("entity1", 0, 0, delta_time);

    if(has_key_pressed(69)) {
        add_entity_position("scary", delta_time, 0, 0);
    }

    if(has_key_pressed(81)) {
        add_entity_position("scary", -delta_time, 0, 0);
    }

    if(has_key_pressed(68)) {
        add_entity_position("scary", 0, delta_time, 0);
    }

    if(has_key_pressed(65)) {
        add_entity_position("scary", 0, -delta_time, 0);
    }

    if(has_key_pressed(87)) {
        add_entity_position("scary", 0, 0, delta_time);
    }

    if(has_key_pressed(83)) {
        add_entity_position("scary", 0, 0, -delta_time);
    }

    
}