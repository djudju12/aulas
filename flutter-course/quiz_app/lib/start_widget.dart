import 'package:flutter/material.dart';
import 'package:quiz_app/title_widget.dart';

class LogoWidget extends StatelessWidget {
  const LogoWidget(this.callback, {super.key});
  final void Function() callback;

  @override
  Widget build(context) {
    return Column(
      mainAxisSize: MainAxisSize.min,
      children: [
        Image.asset(
          "assets/images/quiz-logo.png",
          width: 200,
          color: const Color.fromARGB(150, 255, 255, 255),
        ),
        const SizedBox(
          height: 65,
        ),
        const TitleText("Learn Flutter the fun way!"),
        const SizedBox(
          height: 5,
        ),
        OutlinedButton.icon(
          onPressed: callback,
          style: OutlinedButton.styleFrom(
            foregroundColor: Colors.white,
            textStyle: const TextStyle(fontSize: 14),
          ),
          icon: const Icon(Icons.arrow_right_alt),
          label: const Text("Start quiz"),
        )
      ],
    );
  }
}
