//
// Created by Vin on 3/24/2025.
//

#ifndef OBJECTTRANSFORM_H
#define OBJECTTRANSFORM_H

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace GLpipeline {
    class ObjectTransform {
    private:
        glm::mat4 model;
        glm::vec3 translation, rotation, scale;
        const float radianConverter=0.0174533f;
    public:
        ObjectTransform();

        [[nodiscard]] const glm::vec3& get_translation()  const{//const after the parameters makes sure this cant set to the variable
            return  translation;
        }

        void set_translation(const glm::vec3 t) {
            translation = t;
        }

        [[nodiscard]] const glm::vec3& get_rotation() const {
            return rotation;
        }

        void set_rotation(const glm::vec3 r) {
            rotation = r;
        }

        [[nodiscard]] const glm::vec3& get_scale()  const{
            return scale;
        }

        void set_scale(const glm::vec3 s) {
            scale = s;
        }


        const glm::mat4& get_model();
    };
}



#endif //OBJECTTRANSFORM_H
