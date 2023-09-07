import 'package:flutter/material.dart';
import 'package:quiz_app/data/questions.dart';
import 'package:quiz_app/questions_screen.dart';
import 'package:quiz_app/results_screen.dart';
import 'package:quiz_app/start_widget.dart';

const colors = [
  Color.fromARGB(255, 77, 10, 110),
  Color.fromARGB(255, 102, 24, 141),
];

class Quiz extends StatefulWidget {
  const Quiz({super.key});

  @override
  State<Quiz> createState() {
    return _QuizState();
  }
}

class _QuizState extends State<Quiz> {
  var activeScreen = 'START';
  final List<String> answers = [];

  void switchScreen() {
    setState(() {
      activeScreen = 'QUESTIONS';
    });
  }

  void chooseAnswer(String answer) {
    answers.add(answer);
    if (answers.length == questions.length) {
      setState(() {
        activeScreen = 'RESULTS';
      });
    }
  }

  @override
  Widget build(context) {
    Widget screenWidget = LogoWidget(switchScreen);
    switch (activeScreen) {
      case 'START':
        screenWidget = LogoWidget(switchScreen);
      case 'QUESTIONS':
        screenWidget = QuestionsWidget(
          onSelectAnswers: chooseAnswer,
        );
      case 'RESULTS':
        screenWidget = ResultScreen(
          choosenAnswers: answers,
        );
    }

    return MaterialApp(
      home: Scaffold(
        body: Container(
          decoration: const BoxDecoration(
              gradient: LinearGradient(
            colors: colors,
            begin: Alignment.topCenter,
            end: Alignment.bottomCenter,
          )),
          child: Center(
            child: screenWidget,
          ),
        ),
      ),
    );
  }
}
