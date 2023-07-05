#include <vsg/all.h>

#include <iostream>


int main(int, char**)
{
    // implement simply print visitor that traverses the scene graph printing out node types
    struct PrintVisitor : public vsg::Inherit<vsg::ConstVisitor, PrintVisitor>
    {
        size_t indent = 0;

        void apply(const vsg::Object& object) override
        {
            for(size_t i=0; i<indent; ++i) std::cout<<" ";
            std::cout<<"Visiting "<<object.className()<<std::endl;

            indent += 4;
            object.traverse(*this);
            indent -= 4;
        }

        void apply(const vsg::stringValue& value) override
        {
            for(size_t i=0; i<indent; ++i) std::cout<<" ";
            std::cout<<"Visiting "<<value.className()<<" "<<value.value()<<std::endl;
        }

        void apply(const vsg::vec3Value& value) override
        {
            for(size_t i=0; i<indent; ++i) std::cout<<" ";
            std::cout<<"Visiting "<<value.className()<<" "<<value.value()<<std::endl;
        }

        void apply(const vsg::doubleArray& array) override
        {
            for(size_t i=0; i<indent; ++i) std::cout<<" ";
            std::cout<<"Visiting "<<array.className()<<" { ";

            for(auto v : array) std::cout<<v<<" ";

            std::cout<<"}"<<std::endl;
        }
    };

    // create a small graph
    auto leaf = vsg::Objects::create();
    leaf->addChild(vsg::vec3Value::create(1.0f, 2.0f, 3.0f));

    auto nested = vsg::Objects::create();
    nested->addChild(leaf);
    nested->addChild(vsg::doubleArray::create({4.0, 5.0, 6.0}));

    auto root = vsg::Objects::create();
    root->addChild(vsg::stringValue::create("Everybody Loves Raymond"));
    root->addChild(nested);

    // consutruct our visitor and then pass it to root node to invoke the visitor.
    PrintVisitor print;
    root->accept(print);

    return 0;
}
