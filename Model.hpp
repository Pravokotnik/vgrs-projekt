#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void zmagovalec(int zmagovalec);
    void checkzmagovalec();

protected:
    ModelListener* modelListener;
    int pinstate = 0;
};

#endif // MODEL_HPP
