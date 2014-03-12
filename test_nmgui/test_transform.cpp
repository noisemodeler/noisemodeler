#include "../nmgui/rendering/transform3d.hpp"

#include <QMatrix4x4>

#include <gtest/gtest.h>

using namespace nmgui;

std::ostream& operator<<(std::ostream &out, const QVector4D &v){
    out << "<" << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.w() << ">";
    return out;
}

std::ostream& operator<<(std::ostream &out, const QVector3D &v){
    out << "<" << v.x() << ", " << v.y() << ", " << v.z() << ">";
    return out;
}

std::ostream& operator<<(std::ostream &out, const QQuaternion &q){
    out << "{<" << q.x() << ", " << q.y() << ", " << q.z() << ">, " << q.scalar() << "}";
    return out;
}

std::ostream& operator<<(std::ostream &out, const QMatrix4x4 &m){
    for (int row = 0; row < 4; ++row) {
        out << m.row(row) << "\n";
    }
    return out;
}

bool isSimilar(const QVector4D &lhs, const QVector4D &rhs){
    return (lhs - rhs).length() < 0.01;
}

bool isSimilar(const QVector3D &lhs, const QVector3D &rhs){
    return (lhs - rhs).length() < 0.01;
}


TEST(TransformTest, Initialization){
    Transform3D t;
    EXPECT_EQ(QVector3D(0,0,0), t.position());
    EXPECT_EQ(QQuaternion(1, {0,0,0}), t.orientation());
    EXPECT_EQ(QMatrix4x4(), t.worldToLocalMatrix());
}

TEST(TransformTest, YawAtOrigin){
    Transform3D t;
    t.yaw(90); //turn 90 degrees to the left
    QMatrix4x4 m = t.worldToLocalMatrix();
    EXPECT_TRUE(isSimilar(QVector4D(1,0,0,1), m * QVector4D(0,0,-1,1))); //straight ahead should appear to be on the right
    EXPECT_TRUE(isSimilar(QVector4D(0,0,1,1), m * QVector4D(1,0,0,1))); //right should appear to be behind us (remember positive z is backwards)
    EXPECT_TRUE(isSimilar(QVector4D(0,1,0,1), m * QVector4D(0,1,0,1))); //up should not be moved
}

TEST(TransformTest, PitchAtOrigin){
    Transform3D t;
    t.pitch(90); //look upwards
    QMatrix4x4 m = t.worldToLocalMatrix();
    EXPECT_TRUE(isSimilar(QVector4D(1,0,0,1), m * QVector4D(1,0,0,1))); //right should still be right
    EXPECT_TRUE(isSimilar(QVector4D(0,0,-1,1), m * QVector4D(0,1,0,1))); //up should now be forwards
    EXPECT_TRUE(isSimilar(QVector4D(0,-1,0,1), m * QVector4D(0,0,-1,1))); //forwards should now be downwards
}

TEST(TransformTest, Move){
    Transform3D t;
    t.moveForward(1);
    t.moveRight(2);
    QMatrix4x4 m = t.worldToLocalMatrix();
    EXPECT_EQ(QVector3D(2,0,-1), t.position());
    EXPECT_TRUE(isSimilar(QVector4D(-2,0,1,1), m * QVector4D(0,0,0,1)));  //origin should now be behind us to the left
    EXPECT_TRUE(isSimilar(QVector4D(0,0,0,1), m * QVector4D(2,0,-1,1)));  //the new origin should be at 2,0,-1
}


TEST(TransformTest, MoveYawMove){
    Transform3D t;
    t.moveForward(1);
    EXPECT_EQ(QVector3D(0,0,-1), t.position());
    t.yaw(-90); //turn right
    EXPECT_EQ(QQuaternion::fromAxisAndAngle({0, 1, 0}, -90), t.orientation());
    t.moveForward(2);
    EXPECT_TRUE(isSimilar(QVector3D(2,0,-1), t.position()));

    QMatrix4x4 m = t.worldToLocalMatrix();
    EXPECT_TRUE(isSimilar(QVector4D(1,0,2,1), m * QVector4D(0,0,0,1)));  //origin should now be behind us to the right
    EXPECT_TRUE(isSimilar(QVector3D(2,0,-1), t.position()));

    EXPECT_TRUE(isSimilar(QVector4D(0,0,-1,1), m * QVector4D(3,0,-1,1))); //checking that stuff in front appears in front
    EXPECT_TRUE(isSimilar(QVector4D(0,0,0,1), m * QVector4D(2,0,-1,1))); //checking that the position is now the new center
    t.setPosition({0,0,0});
}

TEST(TransformTest, MovePitchMoveStrafe){
    Transform3D t;
    t.moveRight(1);
    EXPECT_EQ(QVector3D(1,0,0), t.position());
    t.pitch(-90); //turn downward
    EXPECT_EQ(QQuaternion::fromAxisAndAngle({1, 0, 0}, -90), t.orientation());
    t.moveForward(2); //move two downward
    EXPECT_TRUE(isSimilar(QVector3D(1,-2,0), t.position()));
    t.moveRight(3);
    EXPECT_TRUE(isSimilar(QVector3D(4,-2,0), t.position()));

    QMatrix4x4 m = t.worldToLocalMatrix();
    EXPECT_TRUE(isSimilar(QVector4D(-4,0,2,1), m * QVector4D(0,0,0,1)));
//    std::cout << m * QVector(0,0,0,1);

//    QMatrix4x4 m = t.worldToLocalMatrix();
}
