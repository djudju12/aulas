package com.apidemo.api.dao;

import java.util.List;

import com.apidemo.api.entitys.Student;

public interface StudentDAO {
    
    void save(Student theStudent);
    
    Student findById(Integer id);

    List<Student> findAll();

    List<Student> findByLastName(String lastName);

    void update(Student student);

    void delete(Integer id);
}
