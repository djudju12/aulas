package com.apidemo.api;

import java.util.List;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import com.apidemo.api.dao.StudentDAO;
import com.apidemo.api.entitys.Student;

@SpringBootApplication
public class ApiApplication {

	public static void main(String[] args) {
		SpringApplication.run(ApiApplication.class, args);
	}

	@Bean
	public CommandLineRunner commandLineRunner(StudentDAO studentDAO) {
		return runner -> {
			// createStudent(studentDAO);
			// readStudentByLastName(studentDAO);
			// updateStudent(studentDAO);
			deleteStudent(studentDAO);
		};
	}

	private void deleteStudent(StudentDAO studentDAO) {
		readAllStudent(studentDAO);
		studentDAO.delete(1);
		readAllStudent(studentDAO);
	}

	private void updateStudent(StudentDAO studentDAO) {
		Student student = studentDAO.findById(1);
		System.out.println(student);
		student.setFirstName("JECA");
		student.setLastName("tatu");
		studentDAO.update(student);
		System.out.println(student);
	}

	private void readAllStudent(StudentDAO studentDAO) {
		List<Student> resultSet = studentDAO.findAll();
		for (Student student : resultSet) {
			System.out.println(student);	
		}
	}

	private void readStudentByLastName(StudentDAO studentDAO) {
		List<Student> resultSet = studentDAO.findByLastName("Doe");
		for (Student student : resultSet) {
			System.out.println(student);	
		}
	}

	private void readStudent(StudentDAO studentDAO) {
		Student tempStudent = studentDAO.findById(1);
		System.out.println(tempStudent);
	}

	private void createStudent(StudentDAO studentDAO) {
		System.out.println("Creating new student object");
		Student tempStudent = new Student("Paul", "Doe", "mail@mail.com");

		studentDAO.save(tempStudent);
		System.out.println("Student saved!");
	}
}
