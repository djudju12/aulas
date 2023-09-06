import 'package:flutter/material.dart';
import 'package:first_project/gradient_container.dart';

const colors = [
  Color.fromARGB(255, 18, 18, 18),
  Color.fromARGB(255, 25, 25, 25),
  Color.fromARGB(255, 45, 45, 45),
  Color.fromARGB(255, 70, 70, 70),
  Color.fromARGB(255, 100, 100, 100),
  Color.fromARGB(255, 150, 150, 150),
  Color.fromARGB(255, 200, 200, 200),
];

void main() {
  runApp(const MaterialApp(
    home: Scaffold(
      body: GradientContainer(colors),
    ),
  ));
}
